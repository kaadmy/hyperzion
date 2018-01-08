
#include "client.hpp"

using namespace MClient; // Make this module's namespace local for convenience

/* class Client */

// Constructor/destructor

Client::Client() {
  glfwSetErrorCallback(glfwErrorCb);

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW, aborting." << std::endl;
    std::exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  window = glfwCreateWindow(1024, 600, CONFIG_GAME_TITLE, NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create window, aborting." << std::endl;
    std::exit(1);
  }

  glfwMakeContextCurrent(window);

  filesystem = MCommon::Filesystem::getInstance();
  game = MGame::Game::getInstance();
  renderer = MRenderer::Renderer::getInstance();
}

Client::~Client() {
}

// Singleton getter

Client *Client::getInstance() {
  static Client instance;

  return &instance;
}

// GLFW Callbacks

void Client::glfwErrorCb(int status, const char *message) {
  std::cout << message << std::endl;
}

// Main loop

void Client::main() {
  exit = false; // Reset loop condition when entering the main loop

  while (!exit) {
    glfwPollEvents();

    game->update();

    // Swap buffers and flush

    glfwSwapBuffers(window);

    // Check for exit state

    exit = (exit ? exit : glfwWindowShouldClose(window));
  }
}
