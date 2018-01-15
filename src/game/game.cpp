
#include "game.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Game */

// Constructor/destructor

Game::Game() {
  VERBOSE(std::cout << "Initializing game..." << std::endl);

  filesystem = MCommon::Filesystem::getInstance();
  renderer = MRenderer::Renderer::getInstance();

  // Dummy ship initialization
  // ??? Remove this later for a more robust and actually useful system

  num_ships = 1;
  ships[0] = new Ship();

  // 2D camera

  camera_2d = new MRenderer::Camera(true);

  camera_2d->setAspect(1.0);

  renderer->addCamera(camera_2d);

  // 3D camera

  camera_3d = new MRenderer::Camera(false);

  camera_3d->setFOV(70);
  camera_3d->setAspect(1.0);

  renderer->addCamera(camera_3d);
  renderer->setActiveCamera(camera_3d);
}

Game::~Game() {
  int i;

  VERBOSE(std::cout << "Freeing " << num_ships << " ships..." << std::endl);
  for (i = (num_ships - 1); i > 0; i--) {
    delete ships[i];
  }
}

// Singleton getter

Game *Game::getInstance() {
  static Game instance;

  return &instance;
}

// Deinit

void Game::deinit() {
  VERBOSE(std::cout << "Deinitializing game..." << std::endl);
}

// Update

void Game::update() {
  // Pre-render state setup

  renderer->preDraw();

  // Update game

  int i;

  for (i = 0; i < num_ships; i++) {
    ships[i]->update();
  }

  // 3D Rendering

  for (i = 0; i < num_ships; i++) {
    ships[i]->draw();
  }

  renderer->draw();

  // 2D rendering (HUD, UI)

  // Post-render cleanup

  renderer->postDraw();
}
