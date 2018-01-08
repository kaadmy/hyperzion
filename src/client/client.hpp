
#pragma once

#include "game/game.hpp"
#include "renderer/renderer.hpp"
#include "shared.hpp"
#include "GLFW/glfw3.h"

namespace MClient {
  class Client {
  private:
    Client();

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
