
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Program {
  private:
    bool is_compiled;

    GLuint index;
  public:
    Program();
    ~Program();

    void bind();

    void bindShader(GLenum type, const char *source);
    void link();
  };
}
