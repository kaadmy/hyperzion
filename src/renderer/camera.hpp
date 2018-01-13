
#pragma once

#include "glad.h"
#include "shared.hpp"

namespace MRenderer {
  class Camera {
  private:
    int ident;

    bool ortho;

    GLfloat fov; // X-axis FOV
    GLfloat aspect;

    GLfloat position[3];
    GLfloat angles[3];
  public:
    Camera(bool _ortho);
    ~Camera();

    void bind();

    void setFOV(GLfloat _fov);
    GLfloat getFOV();

    void setAspect(GLfloat _aspect);
    GLfloat getAspect();

    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void getPosition(GLfloat *x, GLfloat *y, GLfloat *z);

    void setAngles(GLfloat x, GLfloat y, GLfloat z);
    void getAngles(GLfloat *x, GLfloat *y, GLfloat *z);
  };
}
