
#include "vbo.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class VBO */

// Constructor/destructor

VBO::VBO() {
  length = 0;

  glGenBuffers(1, &gl_id);

  bind();

  glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
}

VBO::~VBO() {
  glDeleteBuffers(1, &gl_id);
}

// Binding

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, gl_id);

  static const GLsizei stride = sizeof(GLfloat) * 8;

  GLint attrib_position = glGetAttribLocation(gl_id, "v_position");
  glEnableVertexAttribArray(attrib_position);
  glVertexAttribPointer(attrib_position, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);

  GLint attrib_normal = glGetAttribLocation(gl_id, "v_normal");
  glEnableVertexAttribArray(attrib_normal);
  glVertexAttribPointer(attrib_normal, 3, GL_FLOAT, GL_FALSE, stride, (void *) (sizeof(GLfloat) * 3));

  GLint attrib_texcoord = glGetAttribLocation(gl_id, "v_texcoord");
  glEnableVertexAttribArray(attrib_texcoord);
  glVertexAttribPointer(attrib_texcoord, 2, GL_FLOAT, GL_FALSE, stride, (void *) (sizeof(GLfloat) * 6));
}

// Drawing

void VBO::draw(GLint first, GLsizei count) {
  if ((first + count) > length) {
    std::cout << "VBO draw range out of bounds (" << (first + count) << " > " << length<< "), skipping." << std::endl;

    return;
  }

  bind();

  glDrawArrays(GL_TRIANGLES, first, count);
}

// Length getter

GLsizei VBO::getLength() {
  return length;
}
