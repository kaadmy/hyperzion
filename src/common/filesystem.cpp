
#include "filesystem.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

/* class Filesystem */

// Constructor/destructor

Filesystem::Filesystem() {
  is_init = false;
}

Filesystem::~Filesystem() {
}

// Singleton getter

Filesystem *Filesystem::getInstance() {
  static Filesystem instance;

  return &instance;
}

// Initializing and deinitializing

void Filesystem::init(const char *name) {
  if (is_init) {
    return;
  }

  VERBOSE(std::cout << "Initializing filesystem..." << std::endl);

  is_init = true;

  // Initialize PhysFS

  PHYSFS_init(name);

  if (!checkError("PHYSFS_init", "")) {
    std::cout << "Failed to initialize filesystem, ignoring." << std::endl;
  }

  // Enable symlinks

  PHYSFS_permitSymbolicLinks(true);

  // Get path separator

  separator = (char *) PHYSFS_getDirSeparator();
  separatorlength = strlen(separator);

  // Load basedir and mount

  const char *path = (char *) PHYSFS_getBaseDir();

  basedir = (char *) malloc(strlen(path) + separatorlength + strlen(CONFIG_PATH_DATA));

  strcat(basedir, path);
  strcat(basedir, separator);
  strcat(basedir, CONFIG_PATH_DATA);

  if (!mount(basedir, "/")) {
    std::cout << "Failed to mount base dir, ignoring." << std::endl;
  }
}

void Filesystem::deinit() {
  VERBOSE(std::cout << "Deinitializing filesystem..." << std::endl);

  is_init = false;

  PHYSFS_deinit();
}

// Mounting

bool Filesystem::mount(const char *dir, const char *mountpoint) {
  std::cout << "Mounting " << dir << " to " << mountpoint << std::endl;
  PHYSFS_mount(dir, mountpoint, 1); // Append to search path

  return checkError("mount", dir);
}

// Error handling

bool Filesystem::checkError(const char *action, const char *path) {
  PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();

  if (code != PHYSFS_ERR_OK) {
    std::cout << "PhysFS: [" << action << ":" << path << "]: " << PHYSFS_getErrorByCode(code) << std::endl;
  }

  return (code == PHYSFS_ERR_OK);
}
