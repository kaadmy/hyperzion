
#pragma once

#include "renderer/model.hpp"
#include "shared.hpp"

namespace MGame {
  class Ship {
  private:
    float distance;
    float rotation;

    MRenderer::Model *model;
  public:
    Ship();
    ~Ship();

    void update();

    void draw();
  };
}
