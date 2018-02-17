#pragma once

struct Vector3;
struct Matrix;

struct Quaternion {	
	//��]��
	float x;
	float y;
	float z;
	//��]��
	float w;
public:
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	Quaternion(const Vector3& axis, float angle);

	//���K�������߂�
	static Quaternion Normalize(const Quaternion& q);
	//���K������
	Quaternion& Normalize();

	//���ς����߂�
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	//�m���������߂�
	float Length() const;
	//���ʐ��`�⊮
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float amount);
	//��]�s�񂩂�N�I�^�j�I�����쐬
	static Quaternion CreateFromRotationMatrix(const Matrix& matrix);
};

//���Z�q�I�[�o�[���[�h
Quaternion operator -(const Quaternion& q);

Quaternion& operator += (Quaternion& q1, const Quaternion& q2);
Quaternion& operator -= (Quaternion& q1, const Quaternion& q2);
Quaternion& operator *= (Quaternion& q, const float s);
Quaternion& operator /= (Quaternion& q, const float s);
Quaternion& operator *= (Quaternion& q1, const Quaternion& q2);

//0622 &�}�[�N
Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
Quaternion operator * (const Quaternion& q, const float s);
Quaternion operator * (const float s, const Quaternion& q);
Quaternion operator / (const Quaternion& q, const  float s);


/*
�N�I�^�j�I�̗��_
�E��]�s��Ɣ�׈��|�I�ɗv�f�����Ȃ�
�E��]�̕⊮
*/