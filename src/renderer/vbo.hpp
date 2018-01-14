
#pragma once

#include "glad.h"
#include "program.hpp"
#include "shared.hpp"

namespace MRenderer {
  typedef struct {
    GLfloat position[3];
    GLbyte normal[3];
    GLfloat texcoord[2];
  } VertexT;

  class VBO {
  private:
    int ident;

    GLuint gl_id;

    GLenum drawmode;

    GLsizei length;
    VertexT *data;
  public:
    VBO(GLenum _drawmode);
    ~VBO();

    void bindRaw();
    void bind();

    void draw(GLint first, GLsizei count);

    GLsizei getLength();
    void setLength(GLsizei _length);

    VertexT *getVertex(GLsizei index);
  };
}
