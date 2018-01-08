
#include "client/client.hpp"
#include "shared.hpp"

void shutdown(void) {
  std::cout << "Shutdown." << std::endl;
}

int main(int argc, char **argv) {
  std::cout << CONFIG_GAME_TITLE << " v" << CONFIG_VERSION_MAJOR << "." << \
    CONFIG_VERSION_MINOR << "." << CONFIG_VERSION_PATCH << std::endl;

  // Assign atexit handler

  if (std::atexit(shutdown)) {
    std::cout << "Failed to assign exit handler, aborting." << std::endl;
    std::exit(1);
  }

  // Initialize all singletons

  MClient::Client *client = MClient::Client::getInstance();

  // Run client main loop

  client->main();

  return 0; // Clean exit status; calls atexit
}
