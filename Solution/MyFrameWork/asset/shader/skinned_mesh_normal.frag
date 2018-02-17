#version 330
in vec2 out_TexCoord;
in vec3 out_Normal;
in vec3 out_Light;
in vec3 out_View;

layout(location = 0) out vec4 out_FragColor;

uniform vec4 u_lightAmbient;
uniform vec4 u_lightDiffuse;
uniform vec4 u_lightSpecular;

uniform vec4 u_materialAmbient;
uniform vec4 u_materialDiffuse;
uniform vec4 u_materialSpecular;
uniform vec4 u_materialEmission;
uniform float u_materialShiniess;

// テクスチャマップ
uniform sampler2D u_baseMap;
uniform sampler2D u_normalMap;

void main(void) {
  vec3 N = normalize(texture2D(u_normalMap, out_TexCoord).xyz * 2.0 - 1.0);
  vec3 V = normalize(out_View);
  vec3 L = normalize(out_Light);
  vec3 H = normalize(L + V);
  // 拡散反射光の計算
  float diffuse = max(dot(N, L), 0);
  // 鏡面反射光の計算
  float specular = pow(max(dot(N, H), 0),  u_materialShiniess);
  // テクスチャカラーの取得
  vec4 baseColor = texture2D(u_baseMap, out_TexCoord);
  // 最終的なカラーの計算
  vec4 color = u_materialAmbient  * u_lightAmbient  * baseColor
             + u_materialDiffuse  * u_lightDiffuse  * diffuse * baseColor
             + u_materialSpecular * u_lightSpecular * specular
             + u_materialEmission * baseColor;
  out_FragColor.rgb = color.rgb;
  out_FragColor.a = baseColor.a;
}
