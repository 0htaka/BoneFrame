#version 330

in vec2 out_TexCoord;

// テクスチャマップ
uniform sampler2D u_baseMap;

void main(void) {
  gl_FragColor = texture2D(u_baseMap, out_TexCoord);
}
