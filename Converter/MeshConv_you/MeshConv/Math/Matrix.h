#ifndef MATRIX_H_
#define MATRIX_H_

struct Vector3;
struct Quaternion;

struct Matrix {
	float m[4][4];

	// コンストラクタ
	Matrix(
		float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
		float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
		float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
		float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f
	);
	// 拡大縮小
	static Matrix CreateScale(const Vector3& scale);
	// 平行移動
	static Matrix CreateTranslation(const Vector3& translation);
	// 任意軸回転
	static Matrix CreateFromAxisAngle(const Vector3& axis, float angle);
	// クォータニオンから回転行列を作成
	static Matrix CreateFromQuaternion(const Quaternion& quaternion);
	// ヨー・ピッチ・ロールから回転行列を作成
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	// ｘ軸周りの回転
	static Matrix CreateRotationX(float degree);
	// y軸周りの回転
	static Matrix CreateRotationY(float degree);
	// z軸周りの回転
	static Matrix CreateRotationZ(float degree);
	// ワールド行列を作成
	static Matrix CreateWorld(const Vector3& scale, const Quaternion& rotation, const Vector3& translation);
	// ワールド行列を作成
	static Matrix CreateWorld(const Vector3& scale, const Matrix& rotation, const Vector3& translation);
	// ワールド行列を作成
	static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
	// 射影変換行列
	static Matrix CreatePerspectiveFieldOfView(float fov, float aspect, float near, float far);
	// ビュー変換行列を作成
	static Matrix CreateLookAt(const Vector3& position, const Vector3& target, const Vector3& up);

	// 逆行列
	static Matrix Invert(const Matrix& matrix);
	// 転置行列
	static Matrix Transpose(const Matrix& matrix);
	// 線形補間
	static Matrix Lerp(const Matrix& value1, const Matrix& value2, float amount);

	// スケール　回転　平行移動を取得
	void Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;
	// 回転行列の正規化
	static Matrix NormalizeRotationMatrix(const Matrix& matrix);
	// 回転行列の正規化
	Matrix& NormalizeRotationMatrix();

	// 前方ベクトルを取得
	Vector3 Forward() const;
	// 前方ベクトルを設定
	Matrix& Forward(const Vector3& forward);
	// 後方ベクトルを取得
	Vector3 Backward() const;
	// 後方ベクトルを設定
	Matrix& Backward(const Vector3& backward);
	// 上方ベクトルを取得
	Vector3 Up() const;
	// 上方ベクトルを設定
	Matrix& Up(const Vector3& up);
	// 上方ベクトルを取得
	Vector3 Down() const;
	// 上方ベクトルを設定
	Matrix& Down(const Vector3& down);
	// 左方ベクトルを取得
	Vector3 Left() const;
	// 左方ベクトルを設定
	Matrix& Left(const Vector3& left);
	// 右方ベクトルを取得
	Vector3 Right() const;
	// 右方ベクトルを設定
	Matrix& Right(const Vector3& right);
	// 座標を取得
	Vector3 Translation() const;
	// 座標を取得
	Matrix& Translation(const Vector3& translation);
	// スケール値を取得
	Vector3 Scale() const;
	// 回転を取得
	Quaternion Rotation() const;
	// 回転行列を取得
	Matrix RotationMatrix() const;

	// 単位行列
	static const Matrix Identity;
	// ゼロ行列
	static const Matrix Zero;
};

Matrix operator - (const Matrix& v);

Matrix& operator += (Matrix& m1, const Matrix& m2);
Matrix& operator -= (Matrix& m1, const Matrix& m2);
Matrix& operator *= (Matrix& m1, const Matrix& m2);
Matrix& operator *= (Matrix& m1, float s);
Matrix& operator /= (Matrix& m1, float s);

Matrix operator * (Matrix m1, const Matrix& m2);
Matrix operator * (Matrix m, float s);
Matrix operator * (float s, Matrix m);
Matrix operator + (Matrix m1, const Matrix& m2);
Matrix operator - (Matrix m1, const Matrix& m2);
Matrix operator / (Matrix m, float s);

Vector3 operator * (const Vector3& v, const Matrix& m);

#endif

