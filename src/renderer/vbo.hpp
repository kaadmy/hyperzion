
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class VBO {
  private:
    GLuint index;
  public:
    VBO();
    ~VBO();
  };
}
