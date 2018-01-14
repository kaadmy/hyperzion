
#include "camera.hpp"
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Camera */

// Constructor/destructor

Camera::Camera(bool _ortho) {
  ortho = _ortho;
}

Camera::~Camera() {
}

// Binding

void Camera::bind() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// FOV

void Camera::setFOV(GLfloat _fov) {
  fov = _fov;
}

GLfloat Camera::getFOV() {
  return fov;
}

// Aspect

void Camera::setAspect(GLfloat _aspect) {
  aspect = _aspect;
}

GLfloat Camera::getAspect() {
  return aspect;
}

// Position

void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
  position[AXIS_X] = x;
  position[AXIS_Y] = y;
  position[AXIS_Z] = z;
}

void Camera::getPosition(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &position[AXIS_X];
  y = &position[AXIS_Y];
  z = &position[AXIS_Z];
}

// Angles

void Camera::setAngles(GLfloat x, GLfloat y, GLfloat z) {
  angles[AXIS_X] = x;
  angles[AXIS_Y] = y;
  angles[AXIS_Z] = z;
}

void Camera::getAngles(GLfloat *x, GLfloat *y, GLfloat *z) {
  x = &angles[AXIS_X];
  y = &angles[AXIS_Y];
  z = &angles[AXIS_Z];
}
