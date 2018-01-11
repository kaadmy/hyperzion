
import bpy
from bpy.props import *

from bpy_extras.io_utils import ExportHelper

import bmesh

import os
import struct

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

# Big endian binary blob.
# Format:
#  {header: "HZM"}
#  [ushort:tricount]
#  [ubyte:matcount]
#  (([float*3:position], [float*3:normal], [float*2:texcoord]) * 3, [byte:material]) * tricount
#  ([ubyte:namelen], [byte*namelen:name]) * matcount
#
# Limitations:
#  Max triangles: 65536
#  Max materials: 256
#  Max material name length: 256

class Polygon:
    def __init__(self, position, normal, texcoord, material):
        self.position = position
        self.normal = normal
        self.texcoord = texcoord
        self.material = material

    def write(self, debug = False):
        out = ""

        for i in range(3):
            out += str(struct.pack(">fff", self.position[i].x, self.position[i].y, self.position[i].z))
            out += str(struct.pack(">fff", self.normal[i].x, self.normal[i].y, self.normal[i].z))
            out += str(struct.pack(">ff", self.texcoord[i].x, self.texcoord[i].y))

        out += str(struct.pack(">B", self.material))

        return out

    def __repr__(self):
        return repr((self.position, self.normal, self.texcoord, self.material))

def export_mesh(scene, obj):
    out = ""

    out_polygons = ""
    out_materials = ""

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

    for mat in bpy.data.materials:
        out_materials += str(struct.pack(">B", len(mat.name) + 1))
        out_materials += mat.name

    bpy.data.meshes.remove(mesh)

    out += str(struct.pack(">H", len(polygons)))
    out += str(struct.pack(">B", len(bpy.data.materials)))

    out += out_polygons
    out += out_materials

    return out

def export(context, options):
    file=open(options["filepath"], "w")

    out = "HZM"

    if context.active_object.type == "MESH":
        out += export_mesh(context.scene, context.active_object)
    else:
        raise ValueError("Active object not a mesh")

    file.write(out)
    file.close()


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
