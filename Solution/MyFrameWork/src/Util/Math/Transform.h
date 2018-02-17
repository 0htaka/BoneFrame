#pragma once

#include"Vector3.h"
#include"Quaternion.h"

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