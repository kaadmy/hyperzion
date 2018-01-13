
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

bool File::openRead(const char *_path) {
  path = strdup(_path);

  VERBOSE(std::cout << "Opening file " << path << " for reading." << std::endl);

  handle = PHYSFS_openRead(path);

  return builtinOpen();
}

bool File::openWrite(const char *_path) {
  path = strdup(_path);

  VERBOSE(  std::cout << "Opening file " << path << " for writing." << std::endl);

  handle = PHYSFS_openWrite(path);

  return builtinOpen();
}

bool File::openAppend(const char *_path) {
  path = strdup(_path);

  VERBOSE(std::cout << "Opening file " << path << " for appending." << std::endl);

  handle = PHYSFS_openAppend(path);

  return builtinOpen();
}

bool File::builtinOpen() {
  is_open = true;

  if (!filesystem->checkError("PHYSFS_open*", path) || handle == NULL) {
    is_open = false;
  }

  return is_open;
}

void File::close() {
  if (is_open) {
    VERBOSE(std::cout << "Closing file " << path << "." << std::endl);

    is_open = false;

    PHYSFS_close(handle);
    handle = NULL;

    free(path);
  }

  freeData();
}

// Freeing unused data

void File::freeData() {
  if (filedata != NULL) {
    free(filedata);
    filedata = NULL;
  }

  filelength = 0;
}

// Checks and getters

int64_t File::length() {
  if (filelength == 0 && is_open) {
    filelength = PHYSFS_fileLength(handle);
    filesystem->checkError("PHYSFS_fileLength", path);
  }

  return filelength;
}

int64_t File::tell() {
  if (!is_open) {
    return 0;
  }

  int64_t position = PHYSFS_tell(handle);
  filesystem->checkError("PHYSFS_tell", path);

  return position;
}

void File::seek(uint64_t position) {
  PHYSFS_seek(handle, position);
  filesystem->checkError("PHYSFS_seek", path);
}

void File::skip(uint64_t offset) {
  seek(tell() + offset);
}

int File::eof() {
  if (!is_open) {
    return 0;
  }

  return PHYSFS_eof(handle);
}

// Reading

int64_t File::readBytes(char *buffer, uint64_t length) {
  int64_t status = PHYSFS_readBytes(handle, buffer, length);
  filesystem->checkError("PHYSFS_readBytes", path);

  return status;
}

const char *File::read() {
  if (!is_open) {
    return "";
  }

  freeData(); // Ensure cache is clear and force re-read

  length(); // This sets filelength automatically

  filedata = (char *) malloc(filelength);

  readBytes(filedata, filelength);

  filedata[filelength] = '\0'; // ?? Ensure a NUL, is this required?

  //std::cout << filedata << std::endl;

  return filedata;
}

// Byte reading

void File::readSBE16(PHYSFS_sint16 *value) {
  if (!PHYSFS_readSBE16(handle, value)) {
    filesystem->checkError("PHYSFS_readSBE16", path);
  }
}

void File::readUBE16(PHYSFS_uint16 *value) {
  if (!PHYSFS_readUBE16(handle, value)) {
    filesystem->checkError("PHYSFS_readUBE16", path);
  }
}

void File::readSBE32(PHYSFS_sint32 *value) {
  if (!PHYSFS_readSBE32(handle, value)) {
    filesystem->checkError("PHYSFS_readSBE32", path);
  }
}

void File::readUBE32(PHYSFS_uint32 *value) {
  if (!PHYSFS_readUBE32(handle, value)) {
    filesystem->checkError("PHYSFS_readUBE32", path);
  }
}

void File::readSBE64(PHYSFS_sint64 *value) {
  if (!PHYSFS_readSBE64(handle, value)) {
    filesystem->checkError("PHYSFS_readSBE64", path);
  }
}

void File::readUBE64(PHYSFS_uint64 *value) {
  if (!PHYSFS_readUBE64(handle, value)) {
    filesystem->checkError("PHYSFS_readUBE64", path);
  }
}

float File::readFBE() {
  PHYSFS_uint32 value;

  readUBE32(&value);

  return (float) value;
}
