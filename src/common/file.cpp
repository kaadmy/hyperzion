
#include "file.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

/* class File */

// Constructor/destructor

File::File() {
  filesystem = Filesystem::getInstance();

  is_open = false;

  handle = NULL;

  filelength = 0;
  filedata = NULL;
}

File::~File() {
  close();
}

// Open/close

void File::openRead(const char *_path) {
  path = strdup(_path);

  std::cout << "Opening file " << path << " for reading." << std::endl;

  handle = PHYSFS_openRead(path);

  builtinOpen();
}

void File::openWrite(const char *_path) {
  path = strdup(_path);

  std::cout << "Opening file " << path << " for writing." << std::endl;

  handle = PHYSFS_openWrite(path);

  builtinOpen();
}

void File::openAppend(const char *_path) {
  path = strdup(_path);

  std::cout << "Opening file " << path << " for appending." << std::endl;

  handle = PHYSFS_openAppend(path);

  builtinOpen();
}

void File::builtinOpen() {
  is_open = true;

  if (handle == NULL || !filesystem->checkError("open", path)) {
    is_open = false;
  }
}

void File::close() {
  if (is_open) {
    std::cout << "Closing file " << path << "." << std::endl;

    is_open = false;

    PHYSFS_close(handle);

    handle = NULL;
  }

  freeData();
}

// Freeing unused data

void File::freeData() {
  if (filedata != NULL) {
    free(filedata);

    filedata = NULL;
  }
}

// Reading

const char *File::read() {
  if (!is_open) {
    return "";
  }

  freeData(); // Ensure cache is clear and force re-read

  filelength = PHYSFS_fileLength(handle);
  filesystem->checkError("PHYSFS_fileLength", path);

  filedata = (char *) malloc(filelength);

  PHYSFS_readBytes(handle, filedata, filelength);
  filesystem->checkError("PHYSFS_readBytes", path);

  filedata[filelength] = '\0'; // ?? Ensure a NUL, is this required?

  //std::cout << filedata << std::endl;

  return filedata;
}
