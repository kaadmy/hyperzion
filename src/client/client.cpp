
#include "client.hpp"
#include "event.hpp"

using namespace MClient; // Make this module's namespace local for convenience

/* class Client */

// Constructor/destructor

static void callbackError(int status, const char *message) {
  std::cout << message << std::endl;
}

Client::Client() {
  VERBOSE(std::cout << "Initializing client..." << std::endl);

  // Initialize GLFW

  glfwSetErrorCallback(callbackError);

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW, aborting." << std::endl;
    std::exit(1);
  }

  // Ask for an OpenGL 2.1 context

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  // Create window

  window = glfwCreateWindow(1024, 600, CONFIG_GAME_TITLE, NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create window, aborting." << std::endl;
    glfwTerminate();
    std::exit(1);
  }

  glfwMakeContextCurrent(window);

  // Get singletons

  filesystem = MCommon::Filesystem::getInstance();
  game = MGame::Game::getInstance();
  renderer = MRenderer::Renderer::getInstance();

  event = Event::getInstance();
  event->init(window);
}

Client::~Client() {
}

// Singleton getter

Client *Client::getInstance() {
  static Client instance;

  return &instance;
}

// Deinit

void Client::deinit() {
  VERBOSE(std::cout << "Deinitializing client..." << std::endl);

  game->deinit();
  renderer->deinit();
}

// Main loop

void Client::main() {
  exit = false; // Reset loop condition when entering the main loop

  int32_t width;
  int32_t height;

  while (!exit) {
    event->update();

    glfwGetFramebufferSize(window, &width, &height);

    renderer->viewport(width, height);

    game->update();

    // Swap buffers and flush

    glfwSwapBuffers(window);

    // Check for exit state

    exit = (exit ? exit : glfwWindowShouldClose(window));
  }
}
