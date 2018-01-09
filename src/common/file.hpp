
#pragma once

#include "filesystem.hpp"
#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  class File {
  private:
    Filesystem *filesystem;

    bool is_open;

    char *path;

    PHYSFS_File *handle;

    char *data;

    void builtinOpen();
  public:
    File();
    ~File();

    void openRead(const char *name);
    void openWrite(const char *name);
    void openAppend(const char *name);
    void close();

    void freeData();

    const char *read();
  };
}
