
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  const int MAX_TEXTURE_UNITS = 4;

  class Material {
  private:
    int ident;

    class Program *program;

    class Texture *textures[MAX_TEXTURE_UNITS]; // Texture units
  public:
    Material();
    ~Material();

    void bind();
  };
}
