
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

  VERBOSE(std::cout << "Creating texture " << path << "..." << std::endl);

  pixeldata = NULL;

  glGenTextures(1, &gl_id);

  applyParameters();
  load();
}

Texture::~Texture() {
  VERBOSE(std::cout << "Deleting texture " << path << "..." << std::endl);

  free(path);

  stbi_image_free(pixeldata);

  glDeleteTextures(1, &gl_id);
}

// Binding

void Texture::bind(GLenum unit) {
  glActiveTexture(unit); // ??? Is this correct for defining multiple texture units?
  glBindTexture(GL_TEXTURE_2D, gl_id);
}

// Loading/setting parameters

void Texture::load() {
  bind(GL_TEXTURE0);

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
}

void Texture::applyParameters() {
  bind(GL_TEXTURE0);

  // Texture wrap

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

  // Filter

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  // ??? Should we also support mipmaps?
}
