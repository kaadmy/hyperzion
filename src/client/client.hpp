
#pragma once

#include "common/filesystem.hpp"
#include "game/game.hpp"
#include "renderer/renderer.hpp"
#include "shared.hpp"
#include <GLFW/glfw3.h>

namespace MClient {
  class Client {
  private:
    Client();

    MCommon::Filesystem *filesystem;
    MGame::Game *game;
    MRenderer::Renderer *renderer;

    bool exit;

    GLFWwindow *window;

    static void glfwErrorCb(int status, const char *message);
  public:
    ~Client();

    static Client *getInstance();

    void main();
  };
}
