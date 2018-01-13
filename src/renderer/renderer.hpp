
#pragma once

#include "glad.h"
#include "material.hpp"
#include "program.hpp"
#include "shared.hpp"
#include "vbo.hpp"

namespace MRenderer {
  const int MAX_PROGRAMS = 256;
  const int MAX_TEXTURES = 2048;
  const int MAX_MATERIALS = 1024;
  const int MAX_VBOS = 512;

  const int AXIS_X = 0;
  const int AXIS_Y = 1;
  const int AXIS_Z = 2;

  class Renderer { // Singleton
  private:
    Renderer();

    int num_programs;
    int num_textures;
    int num_materials;
    int num_vbos;

    class Program *programs[MAX_PROGRAMS];
    class Texture *textures[MAX_TEXTURES];
    class Material *materials[MAX_MATERIALS];
    class VBO *vbos[MAX_VBOS];
  public:
    ~Renderer();

    static Renderer *getInstance();

    void deinit();

    void preDraw();
    void draw();
    void postDraw();

    int addProgram(Program *program);
    int addTexture(Texture *texture);
    int addMaterial(Material *material);
    int addVBO(VBO *vbo);
  };
}
