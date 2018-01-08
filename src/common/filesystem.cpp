
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

void Filesystem::init(const char *name) {
  if (is_init) {
    return;
  }

  is_init = true;

  std::cout << "Initializing filesystem." << std::endl;

  PHYSFS_init(name);

  PHYSFS_setSaneConfig(CONFIG_GAME_NAME, "", NULL, 0, 0);

  mount(PHYSFS_getBaseDir(), "/");
}

// Mounting

void Filesystem::mount(const char *dir, const char *mountpoint) {
  PHYSFS_mount(dir, mountpoint, 1);
}

// Error handling

bool Filesystem::checkError() {
  PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();

  std::cout << "PhysFS: ";

  switch (code) {
  case PHYSFS_ERR_NOT_FOUND:
    std::cout << "File not found" << std::endl;
    break;
  default:
    std::cout << PHYSFS_getErrorByCode(code) << std::endl;
    break;
  }

  return (code != PHYSFS_ERR_OK);
}
