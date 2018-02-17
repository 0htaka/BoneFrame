#pragma once

struct Vector3;
struct Matrix;

struct Quaternion {	
	//回転軸
	float x;
	float y;
	float z;
	//回転量
	float w;
public:
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	Quaternion(const Vector3& axis, float angle);

	//正規化を求める
	static Quaternion Normalize(const Quaternion& q);
	//正規化する
	Quaternion& Normalize();

	//内積を求める
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	//ノルムを求める
	float Length() const;
	//球面線形補完
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float amount);
	//回転行列からクオタニオンを作成
	static Quaternion CreateFromRotationMatrix(const Matrix& matrix);
};

//演算子オーバーロード
Quaternion operator -(const Quaternion& q);

Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, const float s);
Quaternion& operator /= (Quaternion& q, const float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

//0622 &マーク
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, const float s);
Quaternion operator * (const float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, const  float s);


/*
クオタニオの利点
・回転行列と比べ圧倒的に要素が少ない
・回転の補完
*/