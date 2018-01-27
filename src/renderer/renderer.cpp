
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

  // Display and check OpenGL version

  std::cout << "OpenGL loaded:" << std::endl;
  std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

  if (!GLAD_GL_VERSION_2_1) {
    std::cout << "OpenGL version 2.1 or greater required, aborting." << std::endl;
    std::exit(1);
  }

  // Reset singleton state

  num_programs = 0;
  num_textures = 0;
  num_materials = 0;
  num_vbos = 0;
  num_models = 0;
  num_cameras = 0;

  setActiveCamera(NULL);

  // OpenGL state

  glClearColor(0.1, 0.1, 0.1, 1.0);

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
  for (i = 0; i < num_cameras; i++) {
    if (cameras[i] != NULL) {
      delete cameras[i];
    }
  }

  VERBOSE(std::cout << "Freeing " << num_models << " models..." << std::endl);
  for (i = 0; i < num_models; i++) {
    if (models[i] != NULL) {
      delete models[i];
    }
  }

  VERBOSE(std::cout << "Freeing " << num_vbos << " VBOs..." << std::endl);
  for (i = 0; i < num_vbos; i++) {
    if (vbos[i] != NULL) {
      delete vbos[i];
    }
  }

  VERBOSE(std::cout << "Freeing " << num_materials << " materials..." << std::endl);
  for (i = 0; i < num_materials; i++) {
    if (materials[i] != NULL) {
      delete materials[i];
    }
  }

  VERBOSE(std::cout << "Freeing " << num_textures << " textures..." << std::endl);
  for (i = 0; i < num_textures; i++) {
    if (textures[i] != NULL) {
      delete textures[i];
    }
  }

  VERBOSE(std::cout << "Freeing " << num_programs << " programs..." << std::endl);
  for (i = 0; i < num_programs; i++) {
    if (programs[i] != NULL) {
      removeProgram(programs[i]);
    }
  }
}

// Viewport/camera

void Renderer::viewport(GLint width, GLint height) {
  glViewport(0, 0, width, height);
}

// Camera

void Renderer::setActiveCamera(Camera *camera) {
  active_camera = camera;
}

// Drawing

void Renderer::preDraw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (active_camera != NULL) {
    active_camera->bind();
  } else { // The camera resets matrix  state if available
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}

void Renderer::draw() {
  int i;

  for (i = 0; i < num_models; i++) {
    models[i]->draw();
  }
}

void Renderer::postDraw() {
}

// Adding state

int Renderer::addProgram(Program *program) {
  int index = num_programs;
  num_programs++;

  VERBOSE(std::cout << "Adding program ID " << index << " to renderer..." << std::endl);

  program->ident = index;

  programs[index] = program;

  return index;
}

int Renderer::addTexture(Texture *texture) {
  int index = num_textures;
  num_textures++;

  VERBOSE(std::cout << "Adding texture ID " << index << " to renderer..." << std::endl);

  texture->ident = index;

  textures[index] = texture;

  return index;
}

int Renderer::addMaterial(Material *material) {
  int index = num_materials;
  num_materials++;

  VERBOSE(std::cout << "Adding material ID " << index << " to renderer..." << std::endl);

  material->ident = index;

  materials[index] = material;

  return index;
}

int Renderer::addVBO(VBO *vbo) {
  int index = num_vbos;
  num_vbos++;

  VERBOSE(std::cout << "Adding VBO ID " << index << " to renderer..." << std::endl);

  vbo->ident = index;

  vbos[index] = vbo;

  return index;
}

int Renderer::addModel(Model *model) {
  int index = num_models;
  num_models++;

  VERBOSE(std::cout << "Adding model ID " << index << " to renderer..." << std::endl);

  model->ident = index;

  models[index] = model;

  return index;
}

int Renderer::addCamera(Camera *camera) {
  int index = num_cameras;
  num_cameras++;

  VERBOSE(std::cout << "Adding camera ID " << index << " to renderer..." << std::endl);

  camera->ident = index;

  cameras[index] = camera;

  return index;
}

// Removing state

void Renderer::removeProgram(Program *program) {
  int index = program->ident;

  if (index == (num_programs - 1)) {
    num_programs = index;
  }

  VERBOSE(std::cout << "Removing program ID " << index << " from renderer..." << std::endl);

  delete program;

  programs[index] = NULL;
}

void Renderer::removeTexture(Texture *texture) {
  int index = texture->ident;

  if (index == (num_textures - 1)) {
    num_textures = index;
  }

  VERBOSE(std::cout << "Removing texture ID " << index << " from renderer..." << std::endl);

  delete texture;

  textures[index] = NULL;
}

void Renderer::removeMaterial(Material *material) {
  int index = material->ident;

  if (index == (num_materials - 1)) {
    num_materials = index;
  }

  VERBOSE(std::cout << "Removing material ID " << index << " from renderer..." << std::endl);

  delete material;

  materials[index] = NULL;
}

void Renderer::removeVBO(VBO *vbo) {
  int index = vbo->ident;

  if (index == (num_vbos - 1)) {
    num_vbos = index;
  }

  VERBOSE(std::cout << "Removing VBO ID " << index << " from renderer..." << std::endl);

  delete vbo;

  vbos[index] = NULL;
}

void Renderer::removeModel(Model *model) {
  int index = model->ident;

  if (index == (num_models - 1)) {
    num_models = index;
  }

  VERBOSE(std::cout << "Removing model ID " << index << " from renderer..." << std::endl);

  delete model;

  models[index] = NULL;
}

void Renderer::removeCamera(Camera *camera) {
  int index = camera->ident;

  if (index == (num_cameras - 1)) {
    num_cameras = index;
  }

  VERBOSE(std::cout << "Removing camera ID " << index << " from renderer..." << std::endl);

  delete camera;

  cameras[index] = NULL;
}
