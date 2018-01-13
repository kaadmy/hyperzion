
#pragma once

#include "common/filesystem.hpp"
#include "renderer/material.hpp"
#include "renderer/program.hpp"
#include "renderer/renderer.hpp"
#include "renderer/vbo.hpp"
#include "shared.hpp"
#include "ship.hpp"

namespace MGame {
  const int MAX_SHIPS = 32;

  class Game {
  private:
    Game();

    MCommon::Filesystem *filesystem;
    MRenderer::Renderer *renderer;

    int num_ships;
    class Ship *ships[MAX_SHIPS];
  public:
    ~Game();

    static Game *getInstance();

    void deinit();

    void update();
  };
}
