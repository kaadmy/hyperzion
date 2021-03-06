
#pragma once

#include "camera.hpp"
#include "glad.h"
#include <GL/glu.h>
#include "material.hpp"
#include "model.hpp"
#include "program.hpp"
#include "shared.hpp"
#include "vbo.hpp"

// Axes:
//  +X right
//  +Z forward
//  +Y up

// Rotation order:
// Z roll
// X pitch
// Y yaw

namespace MRenderer {
  const int MAX_PROGRAMS = 32;
  const int MAX_TEXTURES = 1024;
  const int MAX_MATERIALS = 1024;
  const int MAX_VBOS = 512;
  const int MAX_MODELS = 256;
  const int MAX_CAMERAS = 32;

  const int AXIS_X = 0;
  const int AXIS_Y = 1;
  const int AXIS_Z = 2;

  class Renderer { // Singleton
  private:
    Renderer();

    int num_programs;
    int num_textures;
    int num_materials;
    int num_vbos;
    int num_models;
    int num_cameras;

    class Program *programs[MAX_PROGRAMS];
    class Texture *textures[MAX_TEXTURES];
    class Material *materials[MAX_MATERIALS];
    class VBO *vbos[MAX_VBOS];
    class Model *models[MAX_MODELS];
    class Camera *cameras[MAX_CAMERAS];

    class Camera *active_camera;
  public:
    ~Renderer();

    static Renderer *getInstance();

    void deinit();

    void viewport(GLint width, GLint height);

    void setActiveCamera(Camera *camera);

    void preDraw();
    void draw();
    void postDraw();

    int addProgram(Program *program);
    int addTexture(Texture *texture);
    int addMaterial(Material *material);
    int addVBO(VBO *vbo);
    int addModel(Model *model);
    int addCamera(Camera *camera);

    void removeProgram(Program *program);
    void removeTexture(Texture *texture);
    void removeMaterial(Material *material);
    void removeVBO(VBO *vbo);
    void removeModel(Model *model);
    void removeCamera(Camera *camera);
  };
}
