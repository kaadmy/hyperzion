
#include "client/client.hpp"
#include "shared.hpp"
#include "revision.h"

static struct {
  MCommon::Filesystem *filesystem;
  MClient::Client *client;
} main_state;

void shutdown(void) {
  main_state.client->deinit();
  main_state.filesystem->deinit();

  std::cout << "Shutdown." << std::endl;
}

int main(int argc, char **argv) {
  std::cout << CONFIG_GAME_TITLE << " version " << CONFIG_VERSION_STRING << "-" << GIT_REVISION<< std::endl;
  std::cout << "Starting..." << std::endl;

  // Assign atexit handler

  if (std::atexit(shutdown)) {
    std::cout << "Failed to assign exit handler, aborting." << std::endl;
    std::exit(1);
  }

  // Create (and initialize where applicable) singletons

  main_state.filesystem = MCommon::Filesystem::getInstance();
  main_state.filesystem->init(argv[0]);

  main_state.client = MClient::Client::getInstance();

  // Run client main loop

  main_state.client->main();

  return 0; // Clean exit status; calls atexit
}
