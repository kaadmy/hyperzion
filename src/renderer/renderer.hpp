
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Renderer { // Singleton
  private:
    static Renderer *singleton;
  public:
    Renderer();
    ~Renderer();

    Renderer *getInstance();
  };
}
