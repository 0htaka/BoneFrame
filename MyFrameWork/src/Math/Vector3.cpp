#include "Vector3.h"
#include "Matrix.h"
#include "MathHelper.h"

#include <cmath>
#include <algorithm>

const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Backward(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z) {	}

float Vector3::Length() const
{
	return std::sqrt(LengthSquared());
}

float Vector3::LengthSquared() const
{
	return Dot(*this, *this);
}

Vector3 & Vector3::Normalize()
{
	const float len = Length();
	if (len != 0.0f)
		*this /= len;
	return *this;
}

Vector3 Vector3::Normalize(const Vector3 & value)
{
	return Vector3(value).Normalize();
}

float Vector3::Dot(const Vector3 & v1, const Vector3 & v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3 Vector3::Cross(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(
		v1.y*v2.z - v1.z*v2.y,
		v1.z*v2.x - v1.x*v2.z,
		v1.x*v2.y - v1.y*v2.x);
}

float Vector3::Distance(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).Length();
}

float Vector3::DistanceSquared(const Vector3 & v1, const Vector3 & v2)
{
	return (v2 - v1).LengthSquared();
}

Vector3 Vector3::Lerp(const Vector3 & value1, const Vector3 & value2, float amount)
{
	return Vector3(
		Mathf::Lerp(value1.x, value2.x, amount),
		Mathf::Lerp(value1.y, value2.y, amount),
		Mathf::Lerp(value1.z, value2.z, amount));
}

Vector3 Vector3::Min(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(
		std::min(v1.x, v2.x),
		std::min(v1.y, v2.y),
		std::min(v1.z, v2.z));
}

Vector3 Vector3::Max(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(
		std::max(v1.x, v2.x),
		std::max(v1.y, v2.y),
		std::max(v1.z, v2.z));
}

Vector3 Vector3::Clamp(const Vector3 & value1, const Vector3 & min, const Vector3 & max)
{
	return Vector3(
		Mathf::Clamp(value1.x, min.x, max.x),
		Mathf::Clamp(value1.y, min.y, max.y),
		Mathf::Clamp(value1.z, min.z, max.z));
}

Vector3 Vector3::Transform(const Vector3 & pos, const Matrix & mat)
{
	float w = pos.x * mat[0][3] + pos.y * mat[1][3] + pos.z * mat[2][3] + mat[3][3];
	return Vector3(
		(pos.x * mat[0][0] + pos.y * mat[1][0] + pos.z * mat[2][0] + mat[3][0]) / w,
		(pos.x * mat[0][1] + pos.y * mat[1][1] + pos.z * mat[2][1] + mat[3][1]) / w,
		(pos.x * mat[0][2] + pos.y * mat[1][2] + pos.z * mat[2][2] + mat[3][2]) / w
	);
}

Vector3 Vector3::TransformNormal(const Vector3 & pos, const Matrix & mat)
{
	return Vector3(
		pos.x * mat[0][0] + pos.y * mat[1][0] + pos.z * mat[2][0],
		pos.x * mat[0][1] + pos.y * mat[1][1] + pos.z * mat[2][1],
		pos.x * mat[0][2] + pos.y * mat[1][2] + pos.z * mat[2][2]
	);
}

Vector3 Vector3::CreateFromYawPitch(float yaw, float pitch)
{
	return Vector3(
		Mathf::Cos(pitch) * Mathf::Sin(yaw),
		-Mathf::Sin(pitch),
		Mathf::Cos(pitch) * Mathf::Cos(yaw));
}

float Vector3::Pitch() const
{
	float len = Length();
	if (len == 0.0f)
		return 0.0f;
	return Mathf::ASin(-y / len);
}

float Vector3::Yaw() const
{
	if (Length() == 0.0f)
		return 0.0f;
	return Mathf::ATan(x, z);
}

float Vector3::Angle(const Vector3 & from, const Vector3 & to)
{
	float dot = Dot(Normalize(from), Normalize(to));
	//åvéZåÎç∑Ç≈ì‡êœåãâ Ç™-1.0~1.0Çí¥Ç¶ÇÈÇ∆acosÇÕnanÇï‘Ç∑
	return Mathf::ACos(Mathf::Clamp(dot, -1.0f, 1.0f));
}

Vector3 operator-(const Vector3 & v)
{
	return Vector3(-v.x, -v.y, -v.z);
}

Vector3 & operator+=(Vector3 & v1, const Vector3 & v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3 & operator-=(Vector3 & v1, const Vector3 & v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Vector3 & operator*=(Vector3 & v, float s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

Vector3 & operator/=(Vector3 & v, float s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}


Vector3 operator+(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1) += v2;
}

Vector3 operator-(const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1) -= v2;
}

Vector3 operator*(const Vector3 & v, float s)
{
	return Vector3(v) *= s;
}

Vector3 operator*(float s, const  Vector3 & v)
{
	return Vector3(v) *= s;
}

Vector3 operator /(const Vector3 & v, float s)
{
	return Vector3(v) /= s;
}