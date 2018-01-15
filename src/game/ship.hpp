
#pragma once

#include "renderer/model.hpp"
#include "renderer/renderer.hpp"
#include "shared.hpp"

namespace MGame {
  class Ship {
  private:
    float distance;
    float rotation;

    MRenderer::Renderer *renderer;

    MRenderer::Model *model;
  public:
    Ship();
    ~Ship();

    void update();
  };
}
