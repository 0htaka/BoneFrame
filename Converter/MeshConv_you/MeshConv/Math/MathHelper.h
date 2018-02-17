#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

class MathHelper {
public:
	// ��
	static const float Pi;
	// �N�����v 
	static float Clamp(float value, float min, float max);
	// ���̐�Βl
	static float Distance(float n1, float n2);
	// ���`���
	static float Lerp(float value1, float value2, float amount);
	// ���W�A����x�ɕϊ�
	static float ToDegree(float radians);
	// �x�����W�A���ɕϊ�
	static float ToRadians(float degree);
	// �T�C��
	static float Sin(float degree);
	// �R�T�C��
	static float Cos(float degree);
	// �^���W�F���g
	static float Tan(float degree);
	// �t�T�C��	
	static float ASin(float s);
	// �t�R�T�C��	
	static float ACos(float c);
	// �t�^���W�F���g
	static float ATan(float y, float x);
};

#endif


