
#pragma once

#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  class Filesystem {
  private:
    Filesystem();
  public:
    ~Filesystem();

    static Filesystem *getInstance();
  };
}
