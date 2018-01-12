
#include "program.hpp"

using namespace MRenderer; // Make this module's namespace local for convenience

/* class Program */

// Constructor/destructor

Program::Program() {
  gl_id = glCreateProgram();
}

Program::~Program() {
  glDeleteProgram(gl_id);
}

// Binding

void Program::bind() {
  glUseProgram(gl_id);
}

// Creation

void Program::bindShader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader); // If the compile failed, linking will also give the same error log

  glAttachShader(gl_id, shader); // Attach shader to program

  glDeleteShader(shader); // Mark for deletion when program is deleted
}

void Program::link() {
  glLinkProgram(gl_id);

  // Check link status

  GLint status;
  glGetProgramiv(gl_id, GL_LINK_STATUS, &status);

  GLint length;
  GLchar log[512];

  if (status == GL_FALSE) {
    glGetProgramInfoLog(gl_id, 511, &length, &log[0]);
    log[length] = '\0';

    std::cout << "Failed to link program: " << std::endl << log << std::endl;
  }
}
