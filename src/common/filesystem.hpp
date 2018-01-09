
#pragma once

#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  class Filesystem {
  private:
    Filesystem();

    bool is_init;

    char *separator;
    uint8_t separatorlen;

    char *basedir;
  public:
    ~Filesystem();

    static Filesystem *getInstance();

    void init(const char *name);
    bool mount(const char *dir, const char *mountpoint);

    bool checkError(const char *action, const char *path);
  };
}
