
#pragma once

#include "shared.hpp"
#include <GLFW/glfw3.h>

namespace MClient {
  class Event {
  private:
    Event();

    static void glfwKeyCb(int status, const char *message);
  public:
    ~Event();

    static Event *getInstance();

    void init(GLFWwindow *window);
    void update();
  };
}
