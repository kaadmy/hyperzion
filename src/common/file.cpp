
#include "file.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

// Extension helper

char *MCommon::addExtension(const char *path, const char *ext) {
  size_t pathlen = strlen(path);

  char *buf = (char *) malloc(pathlen + strlen(ext));
  strcpy(buf, path);
  strcpy(buf + pathlen, ext);

  return buf;
}

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

  std::cout << "Opening file " << path << " for reading." << std::endl;

  handle = PHYSFS_openRead(path);

  return builtinOpen();
}

bool File::openWrite(const char *_path) {
  path = strdup(_path);

  std::cout << "Opening file " << path << " for writing." << std::endl;

  handle = PHYSFS_openWrite(path);

  return builtinOpen();
}

bool File::openAppend(const char *_path) {
  path = strdup(_path);

  std::cout << "Opening file " << path << " for appending." << std::endl;

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
  if (!is_open) {
    buffer[0] = '\0';

    return 1;
  }

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


  filedata = (char *) malloc(filelength + 1); // NUL

  readBytes(filedata, filelength);

  filedata[filelength] = '\0'; // ?? Ensure a NUL, is this required?


  //std::cout << filedata << std::endl;

  return filedata;
}

// Byte reading

void File::readS8(PHYSFS_sint8 *value) {
  readBytes((char *) value, 1);
}

void File::readU8(PHYSFS_uint8 *value) {
  readBytes((char *) value, 1);
}

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
  PHYSFS_uint8 b0;
  PHYSFS_uint8 b1;
  PHYSFS_uint8 b2;
  PHYSFS_uint8 b3;

  readU8(&b0);
  readU8(&b1);
  readU8(&b2);
  readU8(&b3);

  bool sign = (b0 & 0x80) ? true : false;

  int exponent = ((b0 & ~0x80) << 1 | ((b1 & 0x80) >> 7)) - 126;
  int mantissa = ((b1 & ~0x80) << 16) | (b2 << 8) | b3;

  mantissa += 0x800000;
  if(sign) {
    mantissa = -mantissa;
  }

  return ldexpf(((float) mantissa) / 0x1000000, exponent);
}
