#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;
layout(location = 3) in vec4 in_BoneIndices;
layout(location = 4) in vec4 in_BoneWeight;

out vec2 out_TexCoord;

// ワールド変換行列
uniform mat4 u_matWorld;
// ビュー変換行列
uniform mat4 u_matView;
// 透視変換行列
uniform mat4 u_matProjection;

// ボーンの変換行列
uniform mat4 u_matBones[128];

void main() {
  // テクスチャ座標を出力
  out_TexCoord = in_TexCoord;
  // ボーンの変換行列を計算
  mat4 matLocal = u_matBones[int(in_BoneIndices.x)] * in_BoneWeight.x
                + u_matBones[int(in_BoneIndices.y)] * in_BoneWeight.y
                + u_matBones[int(in_BoneIndices.z)] * in_BoneWeight.z
                + u_matBones[int(in_BoneIndices.w)] * in_BoneWeight.w;
  // ローカル座標系に変換
  vec4 localPosition = matLocal * in_Position;
  // モデリング変換
  vec4 worldPosition = u_matWorld * localPosition;
  // 視野変換
  vec4 viewPosition  = u_matView * worldPosition;
  // 透視変換
  gl_Position  = u_matProjection * viewPosition;
}
