
#pragma once

#include "common/filesystem.hpp"
#include "renderer/material.hpp"
#include "renderer/program.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vbo.hpp"
#include "shared.hpp"

namespace MGame {
  class Game {
  private:
    Game();

    MCommon::Filesystem *filesystem;
    MRenderer::Renderer *renderer;

    MRenderer::Program *test_program;
    MRenderer::Material *test_material;
    MRenderer::VBO *test_vbo;
  public:
    ~Game();

    static Game *getInstance();

    void deinit();

    void update();
  };
}
