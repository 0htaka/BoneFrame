#ifndef MATRIX_H_
#define MATRIX_H_

struct Quaternion;
struct Vector3;

struct Matrix {
	float m[4][4];

	Matrix(
		float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
		float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
		float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
		float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f
	);
	//スケーリングマトリックスを作成
	static Matrix CreateScale(const Vector3 & scale);
	//移動マトリックス作成
	static Matrix CreateTranslation(const Vector3 & translation);
	//任意のベクトルの周囲を回転する新しいマトリックスを作成
	static Matrix CreateFromAxisAngle(const Vector3 & axis, float degree);
	//Quaternionから回転Matrixを作成
	static Matrix Matrix::CreateFromQuaternion(const Quaternion & rotate);
	//指定した yaw , pich , roll でMatrixを作成
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	//ｘ軸を回転軸として頂点のセットを回転させるために使用できるMatrixを作成
	static Matrix CreateRotationX(float degree);
	//ｙ軸を回転軸として頂点のセットを回転させるために使用できるMatrixを作成
	static Matrix CreateRotationY(float degree);
	//ｚ軸を回転軸として頂点のセットを回転させるために使用できるMatrixを作成
	static Matrix CreateRotationZ(float degree);
	//ワールドMatrixを作成
	static Matrix CreateWorld(const Vector3 & scale, const Quaternion & rotation, const Vector3 & translation);
	//ワールドMatrixを作成
	static Matrix CreateWorld(const Vector3 & scale, const Matrix & rotation, const Vector3 & translation);
	////ワールドMatrixを作成
	static Matrix CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up);
	//スクリーン座標系に変換する行列を作成
	static Matrix CreateScreen(float width, float height);
	//視野に基づいて、パースペクティブ射影行列を作成 (右手座標用)
	static Matrix CreatePerspectiveFieldOfView(float fov, float aspect, float near, float);
	//ビュー行列を作成　(右手座標用)
	static Matrix CreateLookAt(const Vector3 & position, const Vector3 & target, const Vector3 & up);

	//逆行列を作成
	static Matrix Invert(const Matrix & m);
	//回転と平行移動のみの逆行列を作成
	Matrix InvertFast(const Matrix& matrix);
	//行列の行と列を入れ替える
	static Matrix Transpose(const Matrix & matrix);
	//２つの行列に対応する値の間を線形補間
	static Matrix Lerp(const Matrix & value1, const Matrix & value2, float amount);

	//３Dスケール	回転				変換（SRT）Matrixからスカラー、変換、回転のコンポーネントを取得
	void Decompose(Vector3 & scale, Quaternion & rotation, Vector3 & translation) const;
	//回転行列の正規化
	static Matrix NormalizeRotationMatrix(const Matrix & matrix);
	//回転行列の正規化
	Matrix & NormalizeRotationMatrix();
	//前方ベクトル取得
	Vector3 Forward() const;
	//前方ベクトル設定
	Matrix & Forward(const Vector3 & forward);
	//後方ベクトル取得
	Vector3 Backward() const;
	//後方ベクトル設定
	Matrix & Backward(const Vector3 & bakward);
	//上方ベクトル取得
	Vector3 Up() const;
	//上方ベクトル設定
	Matrix & Up(const Vector3 & up);
	//下方ベクトル取得
	Vector3 Down() const;
	//下方ベクトル設定
	Matrix & Down(const Vector3 & down);
	//左方ベクトル取得
	Vector3 Left() const;
	//左方ベクトル設定
	Matrix & Left(const Vector3 & left);
	//右方ベクトル取得
	Vector3 Right() const;
	//右方ベクトル設定
	Matrix & Right(const Vector3 & right);


	//平行移動ベクトル取得
	Vector3 Translation() const;
	//平行移動ベクトル設定
	Matrix & Translation(const Vector3 & translation);
	//スケール値取得
	Vector3 Scale() const;
	//回転（Quaternion）の取得
	Quaternion Rotation() const;
	//回転行列の取得
	Matrix RotationMatrix() const;
	//単位行列
	static const Matrix Identity;
	//ゼロ行列
	static const Matrix Zero;

	float* const operator[](const int i);
	const float* const operator[](const int i)const;
};

//float* const operator[](Matrix& m, const int i);

//単項演算しオーバーロード
Matrix operator-(const Matrix & m);

//代入演算子オーバーロード
Matrix & operator+=(Matrix & m1, const Matrix & m2);
Matrix & operator-=(Matrix & m1, const Matrix & m2);
Matrix & operator*=(Matrix & m1, const Matrix & m2);
Matrix & operator*=(Matrix & m, float s);
Matrix & operator/=(Matrix & m, float s);

Matrix operator*(Matrix m1, const Matrix & m2);
Vector3 operator*(const Vector3 & v, const Matrix & m);

//２項演算子オーバーロード
Matrix operator+(Matrix m1, const Matrix & m2);
Matrix operator-(Matrix m1, const Matrix & m2);
Matrix operator*(Matrix m, float s);
Matrix operator*(float s, Matrix m);
Matrix operator/(Matrix m, float s);


#endif // !MATRIX_H_