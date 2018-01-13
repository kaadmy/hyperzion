
#pragma once

#include "glad.h"
#include "program.hpp"
#include "shared.hpp"

namespace MRenderer {
  typedef struct {
    GLfloat position[3];
    GLfloat normal[3];
    GLfloat texcoord[2];
  } Vertex_t;

  class VBO {
  private:
    int ident;

    GLuint gl_id;

    GLsizei size;
    class Vertex *data;
  public:
    VBO();
    ~VBO();

    void bind();

    void draw();
  };
}
