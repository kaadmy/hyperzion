
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Program {
  private:
    GLuint gl_id;
  public:
    Program();
    ~Program();

    void bind();

    void bindShader(GLenum type, const char *source);
    void link();

    int ident;
  };
}
