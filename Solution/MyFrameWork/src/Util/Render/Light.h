#ifndef LIGHT_H_
#define LIGHT_H_

#include "Util/Math/Color.h"
#include "Util/Math/Vector3.h"

struct Light {
	// ŠÂ‹«Œõ
	Color	ambient{ 0.2f, 0.2f, 0.2f, 1.0f };
	// ŠgU”½ËŒõ
	Color	diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
	// ‹¾–Ê”½ËŒõ
	Color	specular{ 1.0f, 1.0f, 1.0f, 1.0f };
	// À•W
	Vector3	position{ 0.0f, 0.0f, 0.0f };
};

#endif

