#ifndef VECTOR3_H_
#define VECTOR3_H_

struct  Matrix;

struct Vector3 {
	float x;
	float y;
	float z;

	// �R���X�g���N�^
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	// ���������߂�
	float Length() const;
	// ���������߂�
	float LengthSquared() const;
	// �P�ʃx�N�g�����쐬���܂�
	Vector3& Normalize();

	// �P�ʃx�N�g�����쐬����
	static Vector3 Normalize(const Vector3& value);
	// �x�N�g���̓���
	static float Dot(const Vector3& vector1, const Vector3& vector2);
	// �x�N�g���̊O��
	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
	// �x�N�g���̋��������߂�
	static float Distance(const Vector3& vector1, const Vector3& vector2);
	// �x�N�g���̋��������߂�
	static float DistanceSuared(const Vector3& vector1, const Vector3& vector2);
	// �x�N�g���̐��`���
	static Vector3 Lerp(const Vector3& vector1, const Vector3& vector2, float amount);
	// �x�N�g���̐����̏������ق���Ԃ�
	static Vector3 Min(const Vector3& vector1, const Vector3& vector2);
	// �x�N�g���̐����̑傫���ق���Ԃ�
	static Vector3 Max(const Vector3& vector1, const Vector3& vector2);

	// �x�N�g���̐����̑傫���ق���Ԃ�
	static Vector3 Clamp(const Vector3& vector1, const Vector3& min, const Vector3& max);
	// �x�N�g���̍��W�ϊ�
	static Vector3 Transform(const Vector3& position, const Matrix& matrix);
	// �@���x�N�g���̍��W�ϊ�
	static Vector3 TransformNormal(const Vector3& position, const Matrix& matrix);
	//�@���[�E�s�b�`����x�N�g�����쐬
	static Vector3 CreateFromYawPicth(float yaw, float pitch);
	//�@�s�b�`���擾
	float Pitch() const;
	//�@���[���擾
	float Yaw() const;
	//�@�Q�̃x�N�g���̊p�x��Ԃ�
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
