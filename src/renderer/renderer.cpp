
#include "renderer.hpp"
#include <GLFW/glfw3.h> // Has to be after glad.h

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Renderer */

// Constructor/destructor

Renderer::Renderer() {
  // Initialize GLAD

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD, aborting." << std::endl;
    std::exit(1);
  }

  // DIsplay and check OpenGL version

  std::cout << "OpenGL loaded:" << std::endl;
  std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

  if (!GLAD_GL_VERSION_2_1) {
    std::cout << "OpenGL version 2.1 or greater required, aborting." << std::endl;
    std::exit(1);
  }

  // OpenGL state

  glClearColor(0.6, 0.8, 0.5, 1.0);
}

Renderer::~Renderer() {
}

// Singleton getter

Renderer *Renderer::getInstance() {
  static Renderer instance;

  return &instance;
}

// Drawing

void Renderer::preDraw() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw() {
}

void Renderer::postDraw() {
}
