
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Camera3D {
  private:
    int ident;

    GLfloat fov;

    GLfloat position[3];
    GLfloat angles[3];
  public:
    Camera3D();
    ~Camera3D();

    void bind();

    void setFOV(GLfloat _fov);
    GLfloat getFOV();

    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void getPosition(GLfloat *x, GLfloat *y, GLfloat *z);

    void setAngles(GLfloat x, GLfloat y, GLfloat z);
    void getAngles(GLfloat *x, GLfloat *y, GLfloat *z);
  };
}
