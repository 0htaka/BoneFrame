#ifndef VECTOR3_H_
#define VECTOR3_H_

struct  Matrix;

struct Vector3 {
	float x;
	float y;
	float z;

	// コンストラクタ
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	// 長さを求める
	float Length() const;
	// 長さを求める
	float LengthSquared() const;
	// 単位ベクトルを作成します
	Vector3& Normalize();

	// 単位ベクトルを作成する
	static Vector3 Normalize(const Vector3& value);
	// ベクトルの内積
	static float Dot(const Vector3& vector1, const Vector3& vector2);
	// ベクトルの外積
	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
	// ベクトルの距離を求める
	static float Distance(const Vector3& vector1, const Vector3& vector2);
	// ベクトルの距離を求める
	static float DistanceSuared(const Vector3& vector1, const Vector3& vector2);
	// ベクトルの線形補間
	static Vector3 Lerp(const Vector3& vector1, const Vector3& vector2, float amount);
	// ベクトルの成分の小さいほうを返す
	static Vector3 Min(const Vector3& vector1, const Vector3& vector2);
	// ベクトルの成分の大きいほうを返す
	static Vector3 Max(const Vector3& vector1, const Vector3& vector2);

	// ベクトルの成分の大きいほうを返す
	static Vector3 Clamp(const Vector3& vector1, const Vector3& min, const Vector3& max);
	// ベクトルの座標変換
	static Vector3 Transform(const Vector3& position, const Matrix& matrix);
	// 法線ベクトルの座標変換
	static Vector3 TransformNormal(const Vector3& position, const Matrix& matrix);
	//　ヨー・ピッチからベクトルを作成
	static Vector3 CreateFromYawPicth(float yaw, float pitch);
	//　ピッチを取得
	float Pitch() const;
	//　ヨーを取得
	float Yaw() const;
	//　２つのベクトルの角度を返す
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

// 
Vector3 operator - (const Vector3& v);

Vector3& operator += (Vector3& v1, const Vector3& v2);
Vector3& operator -= (Vector3& v1, const Vector3& v2);
Vector3& operator *= (Vector3& v1, float s);
Vector3& operator /= (Vector3& v1, float s);

Vector3 operator + (Vector3 v1, const Vector3& v2);
Vector3 operator - (Vector3 v1, const Vector3& v2);
Vector3 operator * (Vector3 v, float s);
Vector3 operator * (float s, Vector3 v);
Vector3 operator / (Vector3 v, float s);

#endif
