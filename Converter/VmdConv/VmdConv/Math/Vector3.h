#ifndef VECTOR3_H_
#define VECTOR3_H_

struct Matrix;

struct Vector3 {
	float x, y, z;

	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	float Length() const;
	float LengthSquared() const;
	Vector3& Normalize();

	static Vector3 Normalize(const Vector3& value);
	static float Dot(const Vector3& v1, const Vector3& v2);
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	static float Distance(const Vector3& v1, const Vector3& v2);
	static float DistanceSquared(const Vector3& v1, const Vector3& v2);
	static Vector3 Lerp(const Vector3& value1, const Vector3& value2, float amount);
	static Vector3 Min(const Vector3& v1, const Vector3& v2);
	static Vector3 Max(const Vector3& v1, const Vector3& v2);
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	static Vector3 Transform(const Vector3& pos, const Matrix& matrix);
	static Vector3 TransformNormal(const Vector3& pos, const Matrix& matrix);
	static Vector3 CreateFromYawPitch(float yaw, float pitch);
	float Pitch() const;
	float Yaw()const;
	static float Angle(const Vector3& from, const Vector3& to);

	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Backward;
	static const Vector3 Forward;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
};

Vector3 operator - (const Vector3& v);

Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v, float s);
Vector3& operator /= (Vector3& v, float s);


Vector3 operator + (const Vector3& v1, const Vector3& v2);
Vector3 operator - (const Vector3& v1, const Vector3& v2);
Vector3 operator * (const Vector3& v, float s);
Vector3 operator * (float s,const Vector3& v);
Vector3 operator / (Vector3 v, float s);

#endif // !VECTOR3_H_
