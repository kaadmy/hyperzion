
#include "filesystem.hpp"

using namespace MCommon; // Make this module's namespace local for convenience

/* class Filesystem */

// Constructor/destructor

Filesystem::Filesystem() {
}

Filesystem::~Filesystem() {
}

// Singleton getter

Filesystem *Filesystem::getInstance() {
  static Filesystem instance;

  return &instance;
}
