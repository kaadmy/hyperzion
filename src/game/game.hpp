
#pragma once

#include "renderer/renderer.hpp"
#include "shared.hpp"

namespace MGame {
  class Game {
  private:
    Game();

    MRenderer::Renderer *renderer;
  public:
    ~Game();

    static Game *getInstance();
  };
}
