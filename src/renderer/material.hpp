
#pragma once

#include "glad.h"
#include "shared.hpp"
#include "texture.hpp"

namespace MRenderer {
  class Material {
  private:
    int ident;

    char *path;

    class Program *program;

    bool texture0_enabled;
    class Texture *texture0;

    bool texture1_enabled;
    class Texture *texture1;

    bool texture2_enabled;
    class Texture *texture2;

    bool texture3_enabled;
    class Texture *texture3;
public:
    Material(Program *_program, const char *_path);
    ~Material();

    void bind();
  };
}
