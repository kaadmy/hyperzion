
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

  file->open("shaders/default.vs", "r");
  test_program->bindShader(GL_VERTEX_SHADER, file->read());

  file->open("shaders/default.fs", "r");
  test_program->bindShader(GL_FRAGMENT_SHADER, file->read());

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
  // Render everything

  renderer->preDraw();

  test_vbo->draw();
  renderer->draw();

  renderer->postDraw();

}
