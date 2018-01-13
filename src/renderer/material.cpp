
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
  program->bind();

  if (texture0_enabled) {
    texture0->bind(GL_TEXTURE0);
  }

  if (texture1_enabled) {
    texture1->bind(GL_TEXTURE1);
  }

  if (texture2_enabled) {
    texture2->bind(GL_TEXTURE2);
  }

  if (texture3_enabled) {
    texture3->bind(GL_TEXTURE3);
  }
}
