
#include "program.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Program */

// Constructor/destructor

Program::Program() {
  index = glCreateProgram();
}

Program::~Program() {
  glDeleteProgram(index);
}

// Binding

void Program::bind() {
  glUseProgram(index);
}

// Creation

void Program::bindShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  // Check compile status

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  GLint length;
  GLchar log[512];

  if (status == GL_FALSE) {
    glGetShaderInfoLog(shader, 511, &length, &log[0]);
    log[length] = '\0';

    std::cout << log << std::endl;
  }

  glAttachShader(index, shader); // Attach shader to program

  glDeleteShader(shader); // Mark for deletion when program is deleted
}

void Program::link() {
  glLinkProgram(index);

  // Check link status

  GLint status;
  glGetProgramiv(index, GL_LINK_STATUS, &status);

  GLint length;
  GLchar log[512];

  if (status == GL_FALSE) {
    glGetProgramInfoLog(index, 511, &length, &log[0]);
    log[length] = '\0';

    std::cout << log << std::endl;
  }

}
