
#include "game.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Game */

// Constructor/destructor

Game::Game() {
  renderer = MRenderer::Renderer::getInstance();
}

Game::~Game() {
}

// Singleton getter

Game *Game::getInstance() {
  static Game instance;

  return &instance;
}

// Update

void Game::update() {
}
