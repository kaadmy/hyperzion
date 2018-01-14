
import bpy
from bpy.props import *

from bpy_extras.io_utils import ExportHelper

import bmesh

import os
import struct
import time

bl_info = {
    "name": "HZM model exporter",
    "author": "KaadmY",
    "version": (0, 1, 0),
    "blender": (2, 79, 0),
    "location": "File > Import-Export",
    "description": "Export HZM model",
    "warning": "Expect stability issues",
    "category": "Import-Export"
}

def mesh_triangulate(me):
    bm = bmesh.new()

    bm.from_mesh(me)
    bmesh.ops.triangulate(bm, faces=bm.faces)
    bm.to_mesh(me)

    bm.free()

def clamp(v, l, h):
    return min(max(v, l), h)

# Big endian binary blob.
# Format:
#  {header: "HZM"}
#  [ubyte:matcount]
#  [ushort:tricount]
#  ([ubyte:namelen], [byte*namelen:name], [ushort:first], [ushort:count]) * matcount
#  (([float*3:position], [byte*3:normal], [float*2:texcoord]) * 3) * tricount
#
# Limitations:
#  Max polygons: 65536
#  Max materials: 256
#  Max material name length: 256

class Polygon:
    def __init__(self, position, normal, texcoord, material):
        self.position = position
        self.normal = normal
        self.texcoord = texcoord
        self.material = material # Only used for sorting

    def write(self, debug = False):
        #print(repr(self))

        out = bytes()

        for i in range(3):
            out += struct.pack(">fff", self.position[i].x, self.position[i].y, self.position[i].z)
            out += struct.pack(">bbb", clamp(int(self.normal[i].x * 256), -128, 127), clamp(int(self.normal[i].y * 256), -128, 127), clamp(int(self.normal[i].z * 256), -128, 127))
            out += struct.pack(">ff", self.texcoord[i].x, self.texcoord[i].y)

        return out

    def __repr__(self):
        return repr((self.position, self.normal, self.texcoord, self.material))

class Material:
    def __init__(self, name, first, count):
        self.name = name
        self.first = first
        self.count = count

    def write(self):
        #print(repr(self))

        out = bytes()

        out += struct.pack(">B", len(self.name))
        out += bytes(self.name, "utf-8")

        out += struct.pack(">H", self.first)
        out += struct.pack(">H", self.count)

        return out

    def __repr__(self):
        return repr((self.name, self.first, self.count))

def export_mesh(scene, obj):
    out = bytes()

    out_polygons = bytes()
    out_materials = bytes()

    mesh = obj.to_mesh(scene, True, "PREVIEW", calc_tessface = False)
    mesh_triangulate(mesh)

    vertices = mesh.vertices[:]
    texcoords = mesh.uv_layers.active.data[:]

    materials = bpy.data.materials

    num_polygons = len(mesh.polygons)
    num_materials = len(bpy.data.materials)

    # Write polygons

    polygons = []

    for poly in mesh.polygons:
        uv = []

        for _, i in enumerate(poly.loop_indices):
            uv.append(texcoords[i].uv)

        p = Polygon(
            [
                vertices[poly.vertices[0]].co,
                vertices[poly.vertices[1]].co,
                vertices[poly.vertices[2]].co
            ],
            [
                vertices[poly.vertices[0]].normal,
                vertices[poly.vertices[1]].normal,
                vertices[poly.vertices[2]].normal
            ],
            uv,
            poly.material_index
        )

        polygons.append(p)

    polygons = sorted(polygons, key = lambda polygon: polygon.material)

    for poly in polygons:
        out_polygons += poly.write()

    # Write materials

    materials = []

    for i in range(len(bpy.data.materials)):
        mat = bpy.data.materials[i]

        first = None
        count = 0

        for j in range(len(polygons)):
            if polygons[j].material == i:
                if first == None:
                    first = j
            elif first != None:
                count = j - first
                break
        else:
            count = (j + 1) - first

        m = Material(
            mat.name,
            first,
            count,
        )

        data = m.write()

        out_materials += data

    bpy.data.meshes.remove(mesh)

    out += struct.pack(">B", len(bpy.data.materials))
    out += struct.pack(">H", len(polygons))

    out += out_materials
    out += out_polygons

    # Print some export stats

    print("Material count: %d" % len(bpy.data.materials))
    print("Polygon count: %d" % len(polygons))

    return out

def export(context, options):
    time_start = time.time()

    file = open(options["filepath"], "wb")

    out = bytes("HZM", "utf-8")

    if context.active_object.type == "MESH":
        out += export_mesh(context.scene, context.active_object)
    else:
        raise ValueError("Active object not a mesh")

    file.write(out)
    file.close()

    time_total = time.time() - time_start

    print("Export took a total of %0.4f seconds" % time_total)

class ExportHZM(bpy.types.Operator, ExportHelper):
    """Export HZM mesh"""

    bl_idname  = "export_object.hzm"
    bl_label   = "Export HZM model"
    bl_options = {"PRESET"}

    filename_ext = ".hzm"
    filter_glob  = StringProperty(
        default = "*.hzm",
        options = {"HIDDEN"},
    )

    def execute(self, context):
        export(context, self.as_keywords())

        return {"FINISHED"}

def menu_func_export(self, context):
    self.layout.operator(ExportHZM.bl_idname, text = "Hyperzion model (.hzm)")

def register():
    bpy.utils.register_module(__name__)

    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_module(__name__)

    bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
