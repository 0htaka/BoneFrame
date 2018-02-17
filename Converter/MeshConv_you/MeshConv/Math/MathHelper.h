#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

class MathHelper {
public:
	// π
	static const float Pi;
	// クランプ 
	static float Clamp(float value, float min, float max);
	// 差の絶対値
	static float Distance(float n1, float n2);
	// 線形補間
	static float Lerp(float value1, float value2, float amount);
	// ラジアンを度に変換
	static float ToDegree(float radians);
	// 度をラジアンに変換
	static float ToRadians(float degree);
	// サイン
	static float Sin(float degree);
	// コサイン
	static float Cos(float degree);
	// タンジェント
	static float Tan(float degree);
	// 逆サイン	
	static float ASin(float s);
	// 逆コサイン	
	static float ACos(float c);
	// 逆タンジェント
	static float ATan(float y, float x);
};

#endif


