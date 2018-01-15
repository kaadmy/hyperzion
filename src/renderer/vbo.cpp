
#include "vbo.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class VBO */

// Constructor/destructor

VBO::VBO(GLenum _drawmode) {
  length = 0;

  drawmode = _drawmode;

  data = NULL;

  glGenBuffers(1, &gl_id);

  setLength(length);
}

VBO::~VBO() {
  glDeleteBuffers(1, &gl_id);

  free(data);
}

// Binding

void VBO::bindRaw() {
  glBindBuffer(GL_ARRAY_BUFFER, gl_id);
}

void VBO::bind() {
  // A valid program must be bound before this call

  bindRaw();

  static const GLsizei stride = (sizeof(GLfloat) * 5) + (sizeof(GLbyte) * 2);

  GLint attrib_position = glGetAttribLocation(gl_id, "v_position");
  glEnableVertexAttribArray(attrib_position);
  glVertexAttribPointer(attrib_position, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0);

  GLint attrib_normal = glGetAttribLocation(gl_id, "v_normal");
  glEnableVertexAttribArray(attrib_normal);
  glVertexAttribPointer(attrib_normal, 3, GL_BYTE, GL_FALSE, stride, (void *) (sizeof(GLfloat) * 3));

  GLint attrib_texcoord = glGetAttribLocation(gl_id, "v_texcoord");
  glEnableVertexAttribArray(attrib_texcoord);
  glVertexAttribPointer(attrib_texcoord, 2, GL_FLOAT, GL_FALSE, stride, (void *) ((sizeof(GLfloat) * 3) + (sizeof(GLbyte) * 3)));
}

// Drawing

void VBO::draw(GLint first, GLsizei count) {
  // A valid program must be bound before this call

  if ((first + count) > length) {
    std::cout << "VBO draw range out of bounds (" << (first + count) << " > " << length << "), skipping." << std::endl;

    return;
  }

  bind();

  glDrawArrays(GL_TRIANGLES, first, count);

  // ??? Test code

  glDisable(GL_TEXTURE_2D);

  glBegin(GL_TRIANGLES);

  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.5, 5.0);

  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.5, -0.5, 5.0);

  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, 5.0);

  glEnd();
}

// Length

GLsizei VBO::getLength() {
  return length;
}

void VBO::setLength(GLsizei _length) {
  length = _length;

  if (data == NULL) {
    data = (VertexT *) realloc(data, length * sizeof(VertexT));
  } else {
    data = (VertexT *) malloc(length * sizeof(VertexT));
  }

  bindRaw();

  glBufferData(GL_ARRAY_BUFFER, length, data, drawmode);
}

// Single vertex data

VertexT *VBO::getVertex(GLsizei index) {
  if (index >= length) {
    std::cout << "VBO vertex fetch out of bounds (" << index << " > " << length << "), skipping." << std::endl;

    return (VertexT *) &data[0];
  }

  return (VertexT *) &data[index];
}
