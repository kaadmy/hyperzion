
#include "file.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

static const size_t FILE_CHUNK_SIZE = 1024;

/* class File */

// Constructor/destructor

File::File() {
  filesystem = Filesystem::getInstance();

  is_open = false;

  handle = NULL;

  data = NULL;
}

File::~File() {
  close();
}

// Open/close

void File::openRead(const char *_path) {
  handle = PHYSFS_openRead(_path);

  path = strdup(_path);
  builtinOpen();
}

void File::openWrite(const char *_path) {
  handle = PHYSFS_openWrite(_path);

  path = strdup(_path);
  builtinOpen();
}

void File::openAppend(const char *_path) {
  handle = PHYSFS_openAppend(_path);

  path = strdup(_path);
  builtinOpen();
}

void File::builtinOpen() {
  is_open = true;

  if (handle == NULL || filesystem->checkError("open", path)) {
    is_open = false;
  }
}

void File::close() {
  if (is_open) {
    is_open = false;

    PHYSFS_close(handle);

    handle = NULL;
  }

  freeData();
}

// Freeing unused data

void File::freeData() {
  if (data != NULL) {
    free(data);

    data = NULL;
  }
}

// Reading

const char *File::read() {
  if (!is_open) {
    return "";
  }

  freeData(); // Ensure cache is clear and force re-read

  size_t size = 0;

  data = (char *) malloc(size);

  while (!PHYSFS_eof(handle)) {
    size += FILE_CHUNK_SIZE;
    data = (char *) realloc(data, size);
    size -= (FILE_CHUNK_SIZE - PHYSFS_readBytes(handle, data, FILE_CHUNK_SIZE));
  }

  data = (char *) realloc(data, size);

  data[size] = '\0'; // Ensure there is a NUL character at the end of the file

  filesystem->checkError("read", path);

  std::cout << data << std::endl;

  return data;
}
