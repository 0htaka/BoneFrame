#pragma once

#include"Math/Vector3.h"
#include"Math/Quaternion.h"

struct Transform
{
public:
	Transform();
	~Transform();

private:
	Vector3 pos;
	Quaternion rot;
	Vector3 scale;
};