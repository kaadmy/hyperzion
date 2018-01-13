
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

  delete file;

  program->link();

  renderer->addProgram(program);

  // Create material(s) automatically
  // ??? Check for existing materials of the same type and state
  // ??? Use model data to load materials

  num_materials = 1;
  materials[0].material = new MRenderer::Material(program, "textures/null");
  materials[0].first = 0;
  materials[0].count = 0;

  renderer->addMaterial(materials[0].material);

  // Create VBO

  vbo = new MRenderer::VBO();

  renderer->addVBO(vbo);
}

Model::~Model() {
  free(name);
}

// Drawing

void Model::draw() {
  int i;

  for (i = 0; i < num_materials; i++) {
    vbo->draw(materials[i].first, materials[i].count);
  }
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
