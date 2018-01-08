
#pragma once

#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  class Filesystem {
  private:
    Filesystem();

    bool is_init;
  public:
    ~Filesystem();

    static Filesystem *getInstance();

    void init(const char *name);
    void mount(const char *dir, const char *mountpoint);

    bool checkError();
  };
}
