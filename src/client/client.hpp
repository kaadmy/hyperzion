
#pragma once

#include "common/filesystem.hpp"
#include "game/game.hpp"
#include "renderer/renderer.hpp"
#include "event.hpp"
#include "shared.hpp"
#include <GLFW/glfw3.h>

namespace MClient {
  class Client {
  private:
    Client();

    MCommon::Filesystem *filesystem;
    MRenderer::Renderer *renderer;
    MGame::Game *game;
    Event *event;

    bool exit;

    GLFWwindow *window;

    static void glfwErrorCb(int status, const char *message);
  public:
    ~Client();

    static Client *getInstance();

    void deinit();

    void main();
  };
}
