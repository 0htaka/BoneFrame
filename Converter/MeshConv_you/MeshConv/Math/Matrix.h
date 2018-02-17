#ifndef MATRIX_H_
#define MATRIX_H_

struct Vector3;
struct Quaternion;

struct Matrix {
	float m[4][4];

	// �R���X�g���N�^
	Matrix(
		float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m14 = 0.0f,
		float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m24 = 0.0f,
		float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f, float m34 = 0.0f,
		float m41 = 0.0f, float m42 = 0.0f, float m43 = 0.0f, float m44 = 1.0f
	);
	// �g��k��
	static Matrix CreateScale(const Vector3& scale);
	// ���s�ړ�
	static Matrix CreateTranslation(const Vector3& translation);
	// �C�ӎ���]
	static Matrix CreateFromAxisAngle(const Vector3& axis, float angle);
	// �N�H�[�^�j�I�������]�s����쐬
	static Matrix CreateFromQuaternion(const Quaternion& quaternion);
	// ���[�E�s�b�`�E���[�������]�s����쐬
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	// ��������̉�]
	static Matrix CreateRotationX(float degree);
	// y������̉�]
	static Matrix CreateRotationY(float degree);
	// z������̉�]
	static Matrix CreateRotationZ(float degree);
	// ���[���h�s����쐬
	static Matrix CreateWorld(const Vector3& scale, const Quaternion& rotation, const Vector3& translation);
	// ���[���h�s����쐬
	static Matrix CreateWorld(const Vector3& scale, const Matrix& rotation, const Vector3& translation);
	// ���[���h�s����쐬
	static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
	// �ˉe�ϊ��s��
	static Matrix CreatePerspectiveFieldOfView(float fov, float aspect, float near, float far);
	// �r���[�ϊ��s����쐬
	static Matrix CreateLookAt(const Vector3& position, const Vector3& target, const Vector3& up);

	// �t�s��
	static Matrix Invert(const Matrix& matrix);
	// �]�u�s��
	static Matrix Transpose(const Matrix& matrix);
	// ���`���
	static Matrix Lerp(const Matrix& value1, const Matrix& value2, float amount);

	// �X�P�[���@��]�@���s�ړ����擾
	void Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;
	// ��]�s��̐��K��
	static Matrix NormalizeRotationMatrix(const Matrix& matrix);
	// ��]�s��̐��K��
	Matrix& NormalizeRotationMatrix();

	// �O���x�N�g�����擾
	Vector3 Forward() const;
	// �O���x�N�g����ݒ�
	Matrix& Forward(const Vector3& forward);
	// ����x�N�g�����擾
	Vector3 Backward() const;
	// ����x�N�g����ݒ�
	Matrix& Backward(const Vector3& backward);
	// ����x�N�g�����擾
	Vector3 Up() const;
	// ����x�N�g����ݒ�
	Matrix& Up(const Vector3& up);
	// ����x�N�g�����擾
	Vector3 Down() const;
	// ����x�N�g����ݒ�
	Matrix& Down(const Vector3& down);
	// �����x�N�g�����擾
	Vector3 Left() const;
	// �����x�N�g����ݒ�
	Matrix& Left(const Vector3& left);
	// �E���x�N�g�����擾
	Vector3 Right() const;
	// �E���x�N�g����ݒ�
	Matrix& Right(const Vector3& right);
	// ���W���擾
	Vector3 Translation() const;
	// ���W���擾
	Matrix& Translation(const Vector3& translation);
	// �X�P�[���l���擾
	Vector3 Scale() const;
	// ��]���擾
	Quaternion Rotation() const;
	// ��]�s����擾
	Matrix RotationMatrix() const;

	// �P�ʍs��
	static const Matrix Identity;
	// �[���s��
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

