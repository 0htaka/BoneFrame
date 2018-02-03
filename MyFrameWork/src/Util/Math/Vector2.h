#ifndef MY_VECTOR2_H_
#define MY_VECTOR2_H_

class Vector2
{
public:
	Vector2(float x = 0.0f, float y = 0.0f);

	Vector2(int x, int y);

	float Length();
	static float Length(Vector2 v);

	float Distance(Vector2 v);
	static float Distance(Vector2 v1, Vector2 v2);

	float Dot(Vector2 v);
	static float Dot(Vector2 v1, Vector2 v2);

	float Cross(Vector2 v);
	static float Cross(Vector2 v1, Vector2 v2);

	Vector2 Normalize();
	static Vector2 Normalize(Vector2 v);

	float Angle(Vector2 v);
	static float Angle(Vector2 v1, Vector2 v2);

	bool Inside(Vector2 min, Vector2 max);
	static bool Inside(Vector2 p, Vector2 min, Vector2 max);

	Vector2 Lerp(const Vector2& begin, const Vector2& end, float rate);

	Vector2 operator -()const;

	Vector2 operator +(const Vector2& v) const;
	Vector2 operator -(const Vector2& v) const;
	Vector2 operator *(const float s) const;
	Vector2 operator /(const float s) const;

	Vector2& operator +=(const Vector2& v);
	Vector2& operator -=(const Vector2& v);
	Vector2& operator *=(const float& s);
	Vector2& operator /=(const float& s);
public:
	float x;
	float y;
};

Vector2& operator *(const float& s, Vector2& v);

#endif // !MY_VECTOR2_H_
