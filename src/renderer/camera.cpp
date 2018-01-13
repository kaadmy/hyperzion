
#include "camera.hpp"
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Camera3D */

// Constructor/destructor

Camera3D::Camera3D() {
}

Camera3D::~Camera3D() {
}

// Binding

void Camera3D::bind() {
}

// FOV

void Camera3D::setFOV(GLfloat _fov) {
  fov = _fov;
}

GLfloat Camera3D::getFOV() {
  return fov;
}

// Position

void Camera3D::setPosition(GLfloat x, GLfloat y, GLfloat z) {
  position[AXIS_X] = x;
  position[AXIS_Y] = y;
  position[AXIS_Z] = z;
}

void Camera3D::getPosition(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &position[AXIS_X];
  y = &position[AXIS_Y];
  z = &position[AXIS_Z];
}

// Angles

void Camera3D::setAngles(GLfloat x, GLfloat y, GLfloat z) {
  angles[AXIS_X] = x;
  angles[AXIS_Y] = y;
  angles[AXIS_Z] = z;
}

void Camera3D::getAngles(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &angles[AXIS_X];
  y = &angles[AXIS_Y];
  z = &angles[AXIS_Z];
}
