
#include "common/file.cpp"
#include "game.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Game */

// Constructor/destructor

Game::Game() {
  filesystem = MCommon::Filesystem::getInstance();
  renderer = MRenderer::Renderer::getInstance();

  test_program = new MRenderer::Program();

  MCommon::File *file = new File();

  file->openRead("data/shaders/default.vs");
  test_program->bindShader(GL_VERTEX_SHADER, file->read());
  file->close();

  file->openRead("data/shaders/default.fs");
  test_program->bindShader(GL_FRAGMENT_SHADER, file->read());
  file->close();

  delete file;

  test_program->link();

  test_vbo = new MRenderer::VBO(test_program);
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

// Update

void Game::update() {
  // Pre-render state setup

  renderer->preDraw();

  // Update game

  // ???

  // 3D Rendering

  test_vbo->draw();
  renderer->draw();

  // 2D rendering (HUD, UI)

  // Post-render cleanup

  renderer->postDraw();
}
