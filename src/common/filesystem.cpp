
#include "filesystem.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

/* class Filesystem */

// Constructor/destructor

Filesystem::Filesystem() {
  is_init = false;
}

Filesystem::~Filesystem() {
  is_init = false;

  PHYSFS_deinit();
}

// Singleton getter

Filesystem *Filesystem::getInstance() {
  static Filesystem instance;

  return &instance;
}

// Initializing and deinitializing

static void printSearchPathCallback(void *data, const char *path) {
  std::cout << "  " << path << std::endl;
}

void Filesystem::init(const char *name) {
  if (is_init) {
    return;
  }

  is_init = true;

  PHYSFS_init(name);

  PHYSFS_permitSymbolicLinks(true);

  if (checkError("fsinit", "")) {
    std::cout << "Failed to initialize filesystem, ignoring." << std::endl;
  }

  separator = (char *) PHYSFS_getDirSeparator();
  separatorlen = strlen(separator);

  PHYSFS_setSaneConfig(CONFIG_ORG_NAME, CONFIG_GAME_NAME, "zip", 0, 1);

  if (checkError("fsconfig", "")) {
    std::cout << "Failed to set filesystem config, ignoring." << std::endl;
  }

  std::cout << "Search path:" << std::endl;
  PHYSFS_getSearchPathCallback(printSearchPathCallback, NULL);
}

// Mounting

void Filesystem::mount(const char *dir, const char *mountpoint) {
  PHYSFS_mount(dir, mountpoint, 1);

  if (checkError("mount", dir)) {
    std::cout << "Failed to mount directory, ignoring." << std::endl;
  }
}

// Error handling

bool Filesystem::checkError(const char *action, const char *path) {
  PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();

  if (code != PHYSFS_ERR_OK) {
    std::cout << "PhysFS: [" << action << ":" << path << "]: " << PHYSFS_getErrorByCode(code) << std::endl;
  }

  return (code != PHYSFS_ERR_OK);
}
