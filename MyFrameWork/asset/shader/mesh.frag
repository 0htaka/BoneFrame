#version 120

uniform sampler2D u_baseMap;

void main(void) {
  gl_FragColor = texture2D(u_baseMap, gl_TexCoord[0].xy);
}
