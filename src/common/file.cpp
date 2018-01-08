
#include "file.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

static const size_t FILE_CHUNK_SIZE = 1024;

/* class File */

// Constructor/destructor

File::File() {
  filesystem = Filesystem::getInstance();

  is_open = false;
}

File::~File() {
}

// Open/close

void File::openRead(const char *name) {
  handle = PHYSFS_openRead(name);
  _open();
}

void File::openWrite(const char *name) {
  handle = PHYSFS_openWrite(name);
  _open();
}

void File::openAppend(const char *name) {
  handle = PHYSFS_openAppend(name);
  _open();
}

void File::_open() {
  is_open = true;

  if (filesystem->checkError()) {
    is_open = false;
  }
}

void File::close() {
  is_open = false;

  PHYSFS_close(handle);

  freeData();
}

// Freeing unused data

void File::freeData() {
  if (data != NULL) {
    free(data);
  }
}

// Reading

const char *File::read() {
  if (!is_open) {
    return "";
  }

  freeData(); // Ensure cache is clear and force re-read

  size_t size = 1; // For NUL

  data = (char *) malloc(size);

  while (!PHYSFS_eof(handle)) {
    size += FILE_CHUNK_SIZE;
    data = (char *) realloc(data, size);
    size -= (FILE_CHUNK_SIZE - PHYSFS_readBytes(handle, data, FILE_CHUNK_SIZE));
  }

  data = (char *) realloc(data, size);

  data[size] = '\0'; // Ensure there is a NUL character at the end of the file

  return data;
}
