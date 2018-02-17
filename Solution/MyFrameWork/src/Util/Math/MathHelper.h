#ifndef MATH_HELPER_H_
#define MATH_HELPER_H_

class Mathf
{
public:
	static const float Pi;
	static float Clamp(float value, float min, float max);
	static float Distance(float n1, float n2);
	static float Lerp(float value1, float value2, float amount);
	static float ToDegrees(float radians);
	static float ToRadians(float degree);
	static float Sin(float degree);
	static float Cos(float degree);
	static float Tan(float degree);
	static float ASin(float s);
	static float ACos(float c);
	static float ATan(float y, float x);
};

#endif // !MATH_HELPER_H_
