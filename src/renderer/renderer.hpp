
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Renderer { // Singleton
  private:
    Renderer();
  public:
    ~Renderer();

    static Renderer *getInstance();

    void preDraw();
    void draw();
    void postDraw();
  };
}
