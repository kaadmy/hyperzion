
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Program {
  private:
    GLuint index;
  public:
    Program();
    ~Program();
  };
}
