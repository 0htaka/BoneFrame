#include "MathHelper.h"
#include <cmath>
#include <algorithm>

const float MathHelper::Pi = 3.14159265359f;

// クランプ 
float MathHelper::Clamp(float value, float min, float max) {
	return std::max(min, std::min(value, max));
}

// 差の絶対値
float MathHelper::Distance(float n1, float n2) {
	return std::abs(n1 - n2);
}

// 線形補間
float MathHelper::Lerp(float value1, float value2, float amount) {
	return (value1 * (1.0f - amount)) + (value2 * amount);
}

// ラジアンを度に変換
float MathHelper::ToDegree(float radians) {
	return radians * (180.0f / MathHelper::Pi);
}

float MathHelper::ToRadians(float degree)
{
	return degree * (MathHelper::Pi /180.0f);
}

float MathHelper::Sin(float degree)
{
	return std::sin(ToRadians(degree));
}

float MathHelper::Cos(float degree)
{
	return std::cos(ToRadians(degree));
}

float MathHelper::Tan(float degree)
{
	return std::tan(ToRadians(degree));
}

float MathHelper::ASin(float s)
{
	return ToDegree(std::asin(s));
}

float MathHelper::ACos(float c)
{
	return ToDegree(std::acos(c));
}

float MathHelper::ATan(float y, float x)
{
	return ToDegree(std::atan2(y, x));
}
