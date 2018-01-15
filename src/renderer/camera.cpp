
#include "camera.hpp"
#include "renderer.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Camera */

// Constructor/destructor

Camera::Camera(bool _ortho) {
  ortho = _ortho;

  setFOV(60.0);
  setAspect(1.0);
  setScale(1.0);

  setClip(0.1, 10.0);

  setPosition(0.0, 0.0, 0.0);
  setAngles(0.0, 0.0, 0.0);
}

Camera::~Camera() {
}

// Binding

void Camera::bind() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Perspective

  GLfloat y = clip_near * tanf((fov * M_PI) / 360);
  GLfloat x = y / aspect;

  glFrustum(-x * scale, x * scale, -y * scale, y * scale, clip_near * scale, clip_far * scale);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Transform for camera coordinates

  glRotatef(-angles[AXIS_Z], 0, 0, 1);
  glRotatef(-angles[AXIS_X], 1, 0, 0);
  glRotatef(-angles[AXIS_Y], 0, 1, 0);

  glTranslatef(-position[AXIS_X], -position[AXIS_Y], -position[AXIS_Z]);
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

// Scale

void Camera::setScale(GLfloat _scale) {
  scale = _scale;
}

GLfloat Camera::getScale() {
  return scale;
}

// Clip

void Camera::setClip(GLfloat near, GLfloat far) {
  clip_near = near;
  clip_far = far;
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
