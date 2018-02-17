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
	//�X�P�[�����O�}�g���b�N�X���쐬
	static Matrix CreateScale(const Vector3 & scale);
	//�ړ��}�g���b�N�X�쐬
	static Matrix CreateTranslation(const Vector3 & translation);
	//�C�ӂ̃x�N�g���̎��͂���]����V�����}�g���b�N�X���쐬
	static Matrix CreateFromAxisAngle(const Vector3 & axis, float degree);
	//Quaternion�����]Matrix���쐬
	static Matrix Matrix::CreateFromQuaternion(const Quaternion & rotate);
	//�w�肵�� yaw , pich , roll ��Matrix���쐬
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	//��������]���Ƃ��Ē��_�̃Z�b�g����]�����邽�߂Ɏg�p�ł���Matrix���쐬
	static Matrix CreateRotationX(float degree);
	//��������]���Ƃ��Ē��_�̃Z�b�g����]�����邽�߂Ɏg�p�ł���Matrix���쐬
	static Matrix CreateRotationY(float degree);
	//��������]���Ƃ��Ē��_�̃Z�b�g����]�����邽�߂Ɏg�p�ł���Matrix���쐬
	static Matrix CreateRotationZ(float degree);
	//���[���hMatrix���쐬
	static Matrix CreateWorld(const Vector3 & scale, const Quaternion & rotation, const Vector3 & translation);
	//���[���hMatrix���쐬
	static Matrix CreateWorld(const Vector3 & scale, const Matrix & rotation, const Vector3 & translation);
	////���[���hMatrix���쐬
	static Matrix CreateWorld(const Vector3 & position, const Vector3 & forward, const Vector3 & up);
	//�X�N���[�����W�n�ɕϊ�����s����쐬
	static Matrix CreateScreen(float width, float height);
	//����Ɋ�Â��āA�p�[�X�y�N�e�B�u�ˉe�s����쐬 (�E����W�p)
	static Matrix CreatePerspectiveFieldOfView(float fov, float aspect, float near, float);
	//�r���[�s����쐬�@(�E����W�p)
	static Matrix CreateLookAt(const Vector3 & position, const Vector3 & target, const Vector3 & up);

	//�t�s����쐬
	static Matrix Invert(const Matrix & m);
	//��]�ƕ��s�ړ��݂̂̋t�s����쐬
	Matrix InvertFast(const Matrix& matrix);
	//�s��̍s�Ɨ�����ւ���
	static Matrix Transpose(const Matrix & matrix);
	//�Q�̍s��ɑΉ�����l�̊Ԃ���`���
	static Matrix Lerp(const Matrix & value1, const Matrix & value2, float amount);

	//�RD�X�P�[��	��]				�ϊ��iSRT�jMatrix����X�J���[�A�ϊ��A��]�̃R���|�[�l���g���擾
	void Decompose(Vector3 & scale, Quaternion & rotation, Vector3 & translation) const;
	//��]�s��̐��K��
	static Matrix NormalizeRotationMatrix(const Matrix & matrix);
	//��]�s��̐��K��
	Matrix & NormalizeRotationMatrix();
	//�O���x�N�g���擾
	Vector3 Forward() const;
	//�O���x�N�g���ݒ�
	Matrix & Forward(const Vector3 & forward);
	//����x�N�g���擾
	Vector3 Backward() const;
	//����x�N�g���ݒ�
	Matrix & Backward(const Vector3 & bakward);
	//����x�N�g���擾
	Vector3 Up() const;
	//����x�N�g���ݒ�
	Matrix & Up(const Vector3 & up);
	//�����x�N�g���擾
	Vector3 Down() const;
	//�����x�N�g���ݒ�
	Matrix & Down(const Vector3 & down);
	//�����x�N�g���擾
	Vector3 Left() const;
	//�����x�N�g���ݒ�
	Matrix & Left(const Vector3 & left);
	//�E���x�N�g���擾
	Vector3 Right() const;
	//�E���x�N�g���ݒ�
	Matrix & Right(const Vector3 & right);


	//���s�ړ��x�N�g���擾
	Vector3 Translation() const;
	//���s�ړ��x�N�g���ݒ�
	Matrix & Translation(const Vector3 & translation);
	//�X�P�[���l�擾
	Vector3 Scale() const;
	//��]�iQuaternion�j�̎擾
	Quaternion Rotation() const;
	//��]�s��̎擾
	Matrix RotationMatrix() const;
	//�P�ʍs��
	static const Matrix Identity;
	//�[���s��
	static const Matrix Zero;

	float* const operator[](const int i);
	const float* const operator[](const int i)const;
};

//float* const operator[](Matrix& m, const int i);

//�P�����Z���I�[�o�[���[�h
Matrix operator-(const Matrix & m);

//������Z�q�I�[�o�[���[�h
Matrix & operator+=(Matrix & m1, const Matrix & m2);
Matrix & operator-=(Matrix & m1, const Matrix & m2);
Matrix & operator*=(Matrix & m1, const Matrix & m2);
Matrix & operator*=(Matrix & m, float s);
Matrix & operator/=(Matrix & m, float s);

Matrix operator*(Matrix m1, const Matrix & m2);
Vector3 operator*(const Vector3 & v, const Matrix & m);

//�Q�����Z�q�I�[�o�[���[�h
Matrix operator+(Matrix m1, const Matrix & m2);
Matrix operator-(Matrix m1, const Matrix & m2);
Matrix operator*(Matrix m, float s);
Matrix operator*(float s, Matrix m);
Matrix operator/(Matrix m, float s);


#endif // !MATRIX_H_