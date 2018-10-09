#include "MathHelper.h"
#include <cmath>
#include <algorithm>

float Mathf::Clamp(float value, float min, float max) {
	return	std::max(min, std::min(value, max));
}

float Mathf::Distance(float n1, float n2) {
	return std::abs(n1 - n2);
}

float Mathf::Lerp(float value1, float value2, float amount) {
	return (value1 * (1.0f - amount)) + (value2 * amount);
}

float Mathf::ToDegrees(float radians) {
	return radians * (180.f / Mathf::Pi);
}

float Mathf::ToRadians(float degree) {
	return degree * (Mathf::Pi / 180.f);
}

float Mathf::Sin(float degree) {
	return std::sin(ToRadians(degree));
}

float Mathf::Cos(float degree) {
	return std::cos(ToRadians(degree));
}

float Mathf::Tan(float degree) {
	return std::tan(ToRadians(degree));
}

float Mathf::ASin(float s) {
	return ToDegrees(std::asin(s));
}

float Mathf::ACos(float c) {
	return ToDegrees(std::acos(c));
}

float Mathf::ATan(float y, float x) {
	return ToDegrees(std::atan2(y, x));
}
