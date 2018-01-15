
#pragma once

#include "glad.h"
#include "material.hpp"
#include "program.hpp"
#include "renderer.hpp"
#include "shared.hpp"

namespace MRenderer {
  const int MAX_MODEL_MATERIALS = 256;

  class Model {
  private:
    class Renderer *renderer;

    char *name;

    GLfloat position[3];
    GLfloat angles[3];

    int num_materials;
    struct {
      class Material *material;
      GLint first;
      GLsizei count;
    } materials[MAX_MODEL_MATERIALS];

    class VBO *vbo;
  public:
    Model(const char *_name);
    ~Model();

    void draw();

    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void getPosition(GLfloat *x, GLfloat *y, GLfloat *z);

    void setAngles(GLfloat x, GLfloat y, GLfloat z);
    void getAngles(GLfloat *x, GLfloat *y, GLfloat *z);

    int ident;
  };
}
