
#include "renderer.hpp"
#include <GLFW/glfw3.h> // Has to be after glad.h

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Renderer */

// Constructor/destructor

Renderer::Renderer() {
  VERBOSE(std::cout << "Initializing renderer..." << std::endl);

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

  // Reset singleton state

  num_programs = 0;
  num_materials = 0;
  num_vbos = 0;

  // OpenGL state

  glClearColor(0.8, 0.8, 0.8, 1.0);

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
}

Renderer::~Renderer() {
}

// Singleton getter

Renderer *Renderer::getInstance() {
  static Renderer instance;

  return &instance;
}

// Deinit

void Renderer::deinit() {
  VERBOSE(std::cout << "Deinitializing renderer..." << std::endl);

  int i;

  VERBOSE(std::cout << "Freeing " << num_cameras << " cameras..." << std::endl);
  for (i = (num_cameras - 1); i > 0; i--) {
    delete cameras[i];
  }

  VERBOSE(std::cout << "Freeing " << num_vbos << " VBOs..." << std::endl);
  for (i = (num_vbos - 1); i > 0; i--) {
    delete vbos[i];
  }

  VERBOSE(std::cout << "Freeing " << num_materials << " materials..." << std::endl);
  for (i = (num_materials - 1); i > 0; i--) {
    delete materials[i];
  }

  VERBOSE(std::cout << "Freeing " << num_textures << " textures..." << std::endl);
  for (i = (num_textures - 1); i > 0; i--) {
    delete textures[i];
  }

  VERBOSE(std::cout << "Freeing " << num_programs << " programs..." << std::endl);
  for (i = (num_programs - 1); i > 0; i--) {
    delete programs[i];
  }
}

// Drawing

void Renderer::preDraw() {
  glClear(GL_COLOR_BUFFER_BIT);
  //glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw() {
}

void Renderer::postDraw() {
}

// Adding state

int Renderer::addProgram(Program *program) {
  int index = num_programs;
  num_programs++;

  VERBOSE(std::cout << "Adding program ID " << index << " to renderer..." << std::endl);

  programs[index] = program;

  return index;
}

int Renderer::addTexture(Texture *texture) {
  int index = num_textures;
  num_textures++;

  VERBOSE(std::cout << "Adding texture ID " << index << " to renderer..." << std::endl);

  textures[index] = texture;

  return index;
}

int Renderer::addMaterial(Material *material) {
  int index = num_materials;
  num_materials++;

  VERBOSE(std::cout << "Adding material ID " << index << " to renderer..." << std::endl);

  materials[index] = material;

  return index;
}

int Renderer::addVBO(VBO *vbo) {
  int index = num_vbos;
  num_vbos++;

  VERBOSE(std::cout << "Adding VBO ID " << index << " to renderer..." << std::endl);

  vbos[index] = vbo;

  return index;
}

int Renderer::addCamera(Camera *camera) {
  int index = num_cameras;
  num_cameras++;

  VERBOSE(std::cout << "Adding camera ID " << index << " to renderer..." << std::endl);

  cameras[index] = camera;

  return index;
}
