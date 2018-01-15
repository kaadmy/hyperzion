
#include "common/file.hpp"
#include "ship.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Ship */

// Constructor/destructor

Ship::Ship() {
  renderer = MRenderer::Renderer::getInstance();

  distance = 0.0;
  rotation = 0.0;

  // Load model

  model = new MRenderer::Model("models/ship/base");

  model->setPosition(0.0, 0.0, 5.0);

  renderer->addModel(model);
}

Ship::~Ship() {
  delete model;
}

// Update

void Ship::update() {
}
