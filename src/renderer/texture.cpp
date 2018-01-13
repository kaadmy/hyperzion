
#include "common/file.hpp"
#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Texture */

// Constructor/destructor

Texture::Texture(const char *_path) {
  path = strdup(_path);

  width = 0;
  height = 0;

  pixeldata = NULL;

  glGenTextures(1, &gl_id);

  applyParameters();
  load();
}

Texture::~Texture() {
  free(path);

  glDeleteTextures(1, &gl_id);
}

// Binding

void Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, gl_id);
}

// Loading/setting parameters

void Texture::load() {
  bind();

  MCommon::File *file = new MCommon::File();

  if (!file->openRead(path)) {
    delete file;

    return;
  }

  pixeldata = stbi_load_from_memory((const uint8_t *) file->read(), file->length(), &width, &height, NULL, 3);

  delete file;

  if (pixeldata == NULL) {
    std::cout << "Failed to load image." << std::endl;
  } else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeldata);
  }

  stbi_image_free(pixeldata);
}

void Texture::applyParameters() {
  bind();

  // Texture wrap

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

  // Filter

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  // ??? Should we also support mipmaps?
}
