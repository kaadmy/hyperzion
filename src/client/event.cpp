
#include "event.hpp"

using namespace MClient; // Make this module's namespace local for convenience

/* class Client */

// Constructor/destructor

Event::Event() {
}

Event::~Event() {
}

// Singleton getter

Event *Event::getInstance() {
  static Event instance;

  return &instance;
}

// Callbacks

static void callbackKey(GLFWwindow *window, int key, int code, int action, int mods) {
  /*
  if (action == GLFW_PRESS) {
    std::cout << "Key press: " << code << std::endl;
  } else if (action == GLFW_RELEASE) {
    std::cout << "Key release: " << code << std::endl;
  }
  */
}

static void callbackCursorPos(GLFWwindow *window, double x, double y) {
  //std::cout << "Cursor position: " << x << ", " << y << std::endl;
}

static void callbackMouseButton(GLFWwindow *window, int button, int action, int mods) {
  /*
  if (action == GLFW_PRESS) {
    std::cout << "Mouse button press: " << button << std::endl;
  } else if (action == GLFW_RELEASE) {
    std::cout << "Mouse button release: " << button << std::endl;
  }
  */
}

// Init

void Event::init(GLFWwindow *window) {
  glfwSetKeyCallback(window, callbackKey);
  glfwSetCursorPosCallback(window, callbackCursorPos);
  glfwSetMouseButtonCallback(window, callbackMouseButton);
}

// Update

void Event::update() {
  glfwPollEvents();
}
