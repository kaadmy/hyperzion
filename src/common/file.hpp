
#pragma once

#include "filesystem.hpp"
#include "shared.hpp"
#include <physfs.h>

namespace MCommon {
  char *addExtension(const char *path, const char *ext);

  class File {
  private:
    Filesystem *filesystem;

    bool is_open;

    char *path;

    PHYSFS_File *handle;

    uint64_t filelength;
    char *filedata;

    bool builtinOpen();
  public:
    File();
    ~File();

    bool openRead(const char *name);
    bool openWrite(const char *name);
    bool openAppend(const char *name);
    void close();

    void freeData();

    int64_t length();
    int64_t tell();
    void seek(uint64_t position);
    void skip(uint64_t offset);
    int eof();

    int64_t readBytes(char *buffer, uint64_t length);
    const char *read();

    void readS8(PHYSFS_sint8 *value);
    void readU8(PHYSFS_uint8 *value);
    void readSBE16(PHYSFS_sint16 *value);
    void readUBE16(PHYSFS_uint16 *value);
    void readSBE32(PHYSFS_sint32 *value);
    void readUBE32(PHYSFS_uint32 *value);
    void readSBE64(PHYSFS_sint64 *value);
    void readUBE64(PHYSFS_uint64 *value);
    float readFBE();
  };
}
