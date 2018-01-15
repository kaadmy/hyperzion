#version 120

attribute vec3 v_position;
attribute vec3 v_normal;
attribute vec2 v_texcoord;

varying vec3 f_normal;
varying vec2 f_texcoord;

void main() {
  f_normal = normalize(v_normal);

  gl_Position = vec4(v_position, 1.0) * gl_ModelViewProjectionMatrix;
}
