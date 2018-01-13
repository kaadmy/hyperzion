
#pragma once

#include "glad.h"
#include "shared.hpp"
#include "stb_image.h"

namespace MRenderer {
  class Texture {
  private:
    int ident;

    char *path;

    uint8_t *pixeldata;

    GLint width;
    GLint height;

    GLenum wrap;
    GLenum filter;
    //GLenum mipmap;

    GLuint gl_id;
  public:
    Texture(const char *_path);
    ~Texture();

    void bind();

    void load();
    void applyParameters();
  };
}
