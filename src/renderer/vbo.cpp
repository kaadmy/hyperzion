
#include "vbo.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class VBO */

// Constructor/destructor

VBO::VBO(Program *program) {
  size = 0;

  glGenBuffers(1, &index);

  bind(program);

  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO() {
}

// Binding

void VBO::bind(Program *program) {
  program->bind();

  glBindBuffer(GL_ARRAY_BUFFER, index);

  static const GLsizei stride = sizeof(GLfloat) * 8;

  GLint attrib_position = glGetAttribLocation(index, "v_position");
  glEnableVertexAttribArray(attrib_position);
  glVertexAttribPointer(attrib_position, 3, GL_FLOAT, GL_FALSE, stride, 0);

  GLint attrib_normal = glGetAttribLocation(index, "v_normal");
  glEnableVertexAttribArray(attrib_normal);
  glVertexAttribPointer(attrib_normal, 3, GL_FLOAT, GL_FALSE, stride, (void *) (sizeof(GLfloat) * 3));

  GLint attrib_texcoord = glGetAttribLocation(index, "v_texcoord");
  glEnableVertexAttribArray(attrib_texcoord);
  glVertexAttribPointer(attrib_texcoord, 2, GL_FLOAT, GL_FALSE, stride, (void *) (sizeof(GLfloat) * 6));
}

// Drawing

void VBO::draw(Program *program) {
  bind(program);

  glDrawArrays(GL_TRIANGLES, 0, size);
}
