
#include "material.hpp"
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Material */

// Constructor/destructor

Material::Material(Program *_program, const char *_path) {
  path = strdup(_path);

  Renderer *renderer = Renderer::getInstance();

  program = _program;

  texture0_enabled = true;
  texture0 = new Texture("textures/null.png"); // ??? Obviously this is a placeholder
  renderer->addTexture(texture0);

  texture1_enabled = false;

  texture2_enabled = false;

  texture3_enabled = false;
}

Material::~Material() {
  free(path);
}

// Binding

void Material::bind() {
  texture0->bind();
}
