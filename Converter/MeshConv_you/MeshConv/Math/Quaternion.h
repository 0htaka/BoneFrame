#ifndef QUATERNION_H_
#define QUATERNION_H_

struct Vector3;
struct Matrix;

struct Quaternion {
	float	x;
	float	y;
	float	z;
	float	w;

	// �R���X�g���N�^
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	// �R���X�g���N�^
	Quaternion(const Vector3& axis, float angle);

	// ���K������
	static Quaternion Normalize(const Quaternion& q);
	// ���K������
	Quaternion& Normalize();

	// ���ς����߂�
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	// �m���������߂�
	float Length() const;

	// ���ʐ��`���
	static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, float amount);

	// ��]�s�񂩂�N�I�[�^�j�I�����쐬
	static Quaternion CreateFormRotationMatrix(const Matrix& matrix);
};

Quaternion operator - (const Quaternion& q);

// ������Z�q�I�[�o�[���[�h
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

