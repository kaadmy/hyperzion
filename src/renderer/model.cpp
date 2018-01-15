
#include "common/file.hpp"
#include "model.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Model */

// Constructor/destructor

Model::Model(const char *_name) {
  name = strdup(_name);

  renderer = Renderer::getInstance();

  setPosition(0.0, 0.0, 0.0);
  setAngles(0.0, 0.0, 0.0);

  VERBOSE(std::cout << "Creating VBO..." << std::endl);

  // Create shader program
  // ??? Check for an existing program of the same type and state

  Program *program = new MRenderer::Program();

  MCommon::File *file = new MCommon::File();

  file->openRead("shaders/default.vs");
  program->bindShader(GL_VERTEX_SHADER, file->read());
  file->close();

  file->openRead("shaders/default.fs");
  program->bindShader(GL_FRAGMENT_SHADER, file->read());
  file->close();

  program->link();

  renderer->addProgram(program);

  // Create VBO

  program->bind();

  vbo = new MRenderer::VBO(GL_STATIC_DRAW);

  renderer->addVBO(vbo);

  // Begin loading

  int i;
  struct {
    char *data;
    uint8_t ubyte;
    uint16_t ushort;
    uint32_t uint;
  } buf;

  buf.data = MCommon::addExtension(name, ".hzm");
  file->openRead(buf.data);
  free(buf.data);

  buf.data = (char *) malloc(256);

  // Check for a valid header

  file->readBytes(buf.data, 3);

  if (strncmp("HZM", buf.data, 3)) {
    std::cout << "Incorrect file format, aborting." << std::endl;

    return;
  }

  file->readU8(&buf.ubyte);
  num_materials = buf.ubyte;

  file->readUBE16(&buf.ushort);
  uint16_t num_polygons = buf.ushort;
  uint32_t num_vertices = num_polygons * 3;

  vbo->setLength(num_vertices); // VBOs take length in vertices

  VERBOSE(std::cout << "Material count: " << num_materials << std::endl);
  VERBOSE(std::cout << "Polygon count: " << num_polygons << std::endl);
  VERBOSE(std::cout << "Vertex count: " << num_vertices << std::endl);

  // Create material(s) automatically

  for (i = 0; i < num_materials; i++) {
    file->readU8(&buf.ubyte);
    uint8_t namelen = buf.ubyte;

    file->readBytes(buf.data, namelen);
    buf.data[namelen] = '\0';
    materials[i].material = new MRenderer::Material(program, buf.data);

    // ??? Check for existing materials of the same type and state
    renderer->addMaterial(materials[i].material);

    file->readUBE16(&buf.ushort);
    materials[i].first = buf.ushort * 3; // Vertices, not triangles

    file->readUBE16(&buf.ushort);
    materials[i].count = buf.ushort * 3; // Vertices, not triangles
  }

  // Load the actual polygon soup

  VertexT *vertex;

  for (i = 0; i < num_polygons; i++) {
    vertex = vbo->getVertex(i);

    vertex->position[AXIS_X] = file->readFBE();
    vertex->position[AXIS_Y] = file->readFBE();
    vertex->position[AXIS_Z] = file->readFBE();

    file->readS8(&vertex->normal[AXIS_X]);
    file->readS8(&vertex->normal[AXIS_Y]);
    file->readS8(&vertex->normal[AXIS_Z]);

    vertex->texcoord[AXIS_X] = file->readFBE();
    vertex->texcoord[AXIS_Y] = file->readFBE();
  }

  // Free references

  free(buf.data);

  delete file;
}

Model::~Model() {
  VERBOSE(std::cout << "Deleting VBO..." << std::endl);

  free(name);
}

// Drawing

void Model::draw() {
  glPushMatrix();

  glRotatef(angles[AXIS_Z], 0, 0, 1);
  glRotatef(angles[AXIS_X], 1, 0, 0);
  glRotatef(angles[AXIS_Y], 0, 1, 0);

  glTranslatef(position[AXIS_X], position[AXIS_Y], position[AXIS_Z]);

  int i;

  for (i = 0; i < num_materials; i++) {
    materials[i].material->bind();
    vbo->draw(materials[i].first, materials[i].count);
  }

  glPopMatrix();
}

// Position

void Model::setPosition(GLfloat x, GLfloat y, GLfloat z) {
  position[AXIS_X] = x;
  position[AXIS_Y] = y;
  position[AXIS_Z] = z;
}

void Model::getPosition(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &position[AXIS_X];
  y = &position[AXIS_Y];
  z = &position[AXIS_Z];
}

// Angles

void Model::setAngles(GLfloat x, GLfloat y, GLfloat z) {
  angles[AXIS_X] = x;
  angles[AXIS_Y] = y;
  angles[AXIS_Z] = z;
}

void Model::getAngles(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &angles[AXIS_X];
  y = &angles[AXIS_Y];
  z = &angles[AXIS_Z];
}
