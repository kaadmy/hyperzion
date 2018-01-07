
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Renderer */

Renderer::Renderer() {
  if (!gladLoadGL()) {
    std::cout << "Failed to initialize GLAD, aborting." << std::endl;
    std::exit(1);
  }

  std::cout << "OpenGL version " << GLVersion.major << "." << GLVersion.minor << " loaded." << std::endl;

  if (!GLAD_GL_VERSION_2_1) {
    std::cout << "OpenGL version 2.1 or greater required, aborting." << std::endl;
    std::exit(1);
  }
}

Renderer::~Renderer() {
}

Renderer *Renderer::getInstance() {
  if (!this->singleton) {
    this->singleton = new Renderer();
  }

  return this->singleton;
}
