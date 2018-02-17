#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;

out vec2 out_TexCoord;

// ワールド変換行列
uniform mat4 u_matWorld;
// ビュー変換行列
uniform mat4 u_matView;
// 透視変換行列
uniform mat4 u_matProjection;

void main() {
  // テクスチャ座標を出力
  out_TexCoord = in_TexCoord;
  // モデリング変換
  vec4 worldPosition = u_matWorld * in_Position;
  // 視野変換
  vec4 viewPosition  = u_matView * worldPosition;
  // 透視変換
  gl_Position  = u_matProjection * viewPosition;
}
