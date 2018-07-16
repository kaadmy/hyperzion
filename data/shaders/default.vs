#version 120

varying vec3 f_normal;
varying vec4 f_texcoord;

void main() {
  f_normal = normalize(gl_Normal);
  f_texcoord = gl_MultiTexCoord0;

  gl_Position = gl_Position * gl_ModelViewProjectionMatrix;
}
