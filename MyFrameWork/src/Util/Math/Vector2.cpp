#include "Vector2.h"
#include "MathHelper.h"
#include <cmath>

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{
}
Vector2::Vector2(int x, int y) :
x((float)x),
y((float)y)
{

}

float Vector2::Length()
{
	return Length(*this);
}

float Vector2::Length(Vector2 v)
{
	return std::sqrtf(v.x*v.x + v.y*v.y);
}

float Vector2::Distance(Vector2 v)
{
	return Distance(*this, v);
}

float Vector2::Distance(Vector2 v1, Vector2 v2)
{
	Vector2 v = v2 - v1;

	return v.Length();
}

float Vector2::Dot(Vector2 v)
{
	return Dot(*this, v);
}

float Vector2::Dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(Vector2 v)
{
	return Cross(*this, v);
}

float Vector2::Cross(Vector2 v1, Vector2 v2)
{
	return v1.x*v2.y - v1.y*v2.x;
}

Vector2 Vector2::Normalize()
{
	float value = 1.0f / Length();

	*this *= value;

	return *this;

}

Vector2 Vector2::Normalize(Vector2 v)
{
	return v.Normalize();
}

float Vector2::Angle(Vector2 v)
{
	return Angle(*this, v);
}

float Vector2::Angle(Vector2 v1, Vector2 v2)
{	//ベクトルAとBの長さを計算する
	float length_A = Length(v1);
	float length_B = Length(v2);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = Dot(v1, v2) / (length_A * length_B);
	//cosθからθを求める
	float sita = acos(cos_sita);

	return sita;
}

bool Vector2::Inside(Vector2 min, Vector2 max)
{
	if (min.x > x || max.x < x) return false;
	if (min.y > y || max.y < y) return false;
	return true;
}

bool Vector2::Inside(Vector2 p, Vector2 min, Vector2 max)
{
	return p.Inside(min, max);
}

Vector2 Vector2::Vector2::Lerp(const Vector2 & begin, const Vector2 & end, float rate)
{
	return Vector2(
		Mathf::Lerp(begin.x, end.x, rate),
		Mathf::Lerp(begin.y, end.y, rate)
		);
}

Vector2 Vector2::operator-()const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2 & v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2 & v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float s) const
{
	return Vector2(x * s, y * s);
}

Vector2 Vector2::operator/(const float s) const
{
	return Vector2(x / s, y / s);
}

Vector2 & Vector2::operator+=(const Vector2 & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2 & Vector2::operator*=(const float & s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2 & Vector2::operator/=(const float & s)
{
	x /= s;
	y /= s;
	return *this;
}

Vector2 & operator*(const float & s, Vector2 & v)
{
	v *= s;
	return v;
}
