#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Vector3;
struct Matrix;

struct Quaternion {
	float	x;
	float	y;
	float	z;
	float	w;

	// コンストラクタ
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	// コンストラクタ
	Quaternion(const Vector3& axis, float angle);

	// 正規化する
	static Quaternion Normalize(const Quaternion& q);
	// 正規化する
	Quaternion& Normalize();

	// 内積を求める
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	// ノルムを求める
	float Length() const;

	// 球面線形補間
	static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, float amount);

	// 回転行列からクオータニオンを作成
	static Quaternion CreateFormRotationMatrix(const Matrix& matrix);
};

Quaternion operator - (const Quaternion& q);

// 代入演算子オーバーロード
Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, float s);
Quaternion& operator /= (Quaternion& q, float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, float s);
Quaternion operator * (float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, float s);

#endif

