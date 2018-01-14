
#include "common/file.hpp"
#include "ship.hpp"

using namespace MGame; // Make this module's namespace local for convenience

/* class Ship */

// Constructor/destructor

Ship::Ship() {
  distance = 0.0;
  rotation = 0.0;

  // Load model

  model = new MRenderer::Model("models/ship/base");
}

Ship::~Ship() {
  delete model;
}

// Update

void Ship::update() {
}

// Drawing

void Ship::draw() {
  model->draw();
}
