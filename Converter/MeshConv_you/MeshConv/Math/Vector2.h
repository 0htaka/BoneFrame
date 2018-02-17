#ifndef VECTOR2_H_
#define VECTOR2_H_

struct Vector2 {
	float x;
	float y;
	// コンストラクタ
	Vector2(float x = 0.0f, float y = 0.0f) :
		x{ x }, y{ y } {
	}
};

#endif