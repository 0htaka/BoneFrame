#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoord;
layout(location = 3) in vec4 in_BoneIndices;
layout(location = 4) in vec4 in_BoneWeight;
layout(location = 5) in vec3 in_Tangent;
layout(location = 6) in vec3 in_Binoaml;

out vec2 out_TexCoord;
out vec3 out_Normal;
out vec3 out_Light;
out vec3 out_View;

// ワールド変換行列
uniform mat4 u_matWorld;
// ビュー変換行列
uniform mat4 u_matView;
// 透視変換行列
uniform mat4 u_matProjection;

// ボーンの変換行列
uniform mat4 u_matBones[128];

// ライトポジション
uniform vec3 u_lightPosition;

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
  // 法線ベクトルの計算
  vec3 localNormal = mat3(matLocal)   * in_Normal;
  vec3 worldNormal = mat3(u_matWorld) * localNormal;
  vec3 viewNormal  = mat3(u_matView)  * worldNormal;
  // 接ベクトルの計算
  vec3 localTangent = mat3(matLocal)   * in_Tangent;
  vec3 worldTangent = mat3(u_matWorld) * localTangent;
  vec3 viewTangent  = mat3(u_matView)  * worldTangent;
  // 従法線ベクトルの計算
  vec3 localBinormal = mat3(matLocal)   * in_Binoaml;
  vec3 worldBinormal = mat3(u_matWorld) * localBinormal;
  vec3 viewBinormal  = mat3(u_matView)  * worldBinormal;
  // 接空間変換行列の作成
  mat3 matTBN = mat3(normalize(viewTangent), normalize(viewBinormal),normalize(viewNormal));
  // 視点方向のベクトルの出力
  out_View = vec3(-viewPosition) * matTBN;
  // ライト方向のベクトルの出力
  out_Light = (u_lightPosition - vec3(viewPosition)) * matTBN;
}
