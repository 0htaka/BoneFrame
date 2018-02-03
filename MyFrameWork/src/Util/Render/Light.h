#ifndef LIGHT_H_
#define LIGHT_H_

#include "Util/Math/Color.h"
#include "Util/Math/Vector3.h"

struct Light {
	// ����
	Color	ambient{ 0.2f, 0.2f, 0.2f, 1.0f };
	// �g�U���ˌ�
	Color	diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
	// ���ʔ��ˌ�
	Color	specular{ 1.0f, 1.0f, 1.0f, 1.0f };
	// ���W
	Vector3	position{ 0.0f, 0.0f, 0.0f };
};

#endif

