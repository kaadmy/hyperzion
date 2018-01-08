
#pragma once

#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  class File {
  private:
    bool is_open;
  public:
    File();
    ~File();

    void open(const char *name, const char *mode = "r");
    void close();

    const char *read();
  };
}
