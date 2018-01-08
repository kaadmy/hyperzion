
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Renderer */

// Constructor/destructor

Renderer::Renderer() {
  if (!gladLoadGL()) {
    std::cout << "Failed to initialize GLAD, aborting." << std::endl;
    std::exit(1);
  }

  std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << " loaded." << std::endl;

  if (!GLAD_GL_VERSION_2_1) {
    std::cout << "OpenGL version 2.1 or greater required, aborting." << std::endl;
    std::exit(1);
  }
}

Renderer::~Renderer() {
}

// Singleton getter

Renderer *Renderer::getInstance() {
  static Renderer instance;

  return &instance;
}
