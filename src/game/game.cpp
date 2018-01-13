
#include "common/file.cpp"
#include "game.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Game */

// Constructor/destructor

Game::Game() {
  VERBOSE(std::cout << "Initializing game..." << std::endl)

  filesystem = MCommon::Filesystem::getInstance();
  renderer = MRenderer::Renderer::getInstance();

  // Create test shader program

  test_program = new MRenderer::Program();

  MCommon::File *file = new File();

  file->openRead("shaders/default.vs");
  test_program->bindShader(GL_VERTEX_SHADER, file->read());
  file->close();

  file->openRead("shaders/default.fs");
  test_program->bindShader(GL_FRAGMENT_SHADER, file->read());
  file->close();

  delete file;

  test_program->link();

  renderer->addProgram(test_program);

  // Create test material

  test_material = new MRenderer::Material(test_program, "textures/null");

  renderer->addMaterial(test_material);

  // Create test VBO

  test_vbo = new MRenderer::VBO();

  renderer->addVBO(test_vbo);
}

Game::~Game() {
  delete test_vbo;
  delete test_program;
}

// Singleton getter

Game *Game::getInstance() {
  static Game instance;

  return &instance;
}

// Deinit

void Game::deinit() {
  VERBOSE(std::cout << "Deinitializing game..." << std::endl)
}

// Update

void Game::update() {
  // Pre-render state setup

  renderer->preDraw();

  // Update game

  // ??? Put game update code here

  // 3D Rendering

  renderer->draw();

  test_material->bind();
  test_vbo->draw();

  // 2D rendering (HUD, UI)

  // Post-render cleanup

  renderer->postDraw();
}
