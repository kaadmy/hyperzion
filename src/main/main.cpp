
#include "client/client.hpp"
#include "shared.hpp"
#include "revision.h"

void shutdown(void) {
  std::cout << "Shutdown." << std::endl;
}

#define CHECKERR(msg) printf("PhysFS [%s]: %s\n", msg, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()))

int main(int argc, char **argv) {
  std::cout << CONFIG_GAME_TITLE << " version " << CONFIG_VERSION_STRING << "-" << GIT_REVISION<< std::endl;

  // Assign atexit handler

  if (std::atexit(shutdown)) {
    std::cout << "Failed to assign exit handler, aborting." << std::endl;
    std::exit(1);
  }

  // Initialize some singletons

  MCommon::Filesystem *filesystem = MCommon::Filesystem::getInstance();

  filesystem->init(argv[0]);

  MClient::Client *client = MClient::Client::getInstance();

  // Run client main loop

  client->main();

  return 0; // Clean exit status; calls atexit
}
