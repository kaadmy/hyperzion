
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
    GLuint index;

    class Program *program;

    GLsizei size;
    class Vertex *data;
  public:
    VBO(Program *program);
    ~VBO();

    void bind();

    void draw();
  };
}
