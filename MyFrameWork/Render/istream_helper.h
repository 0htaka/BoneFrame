#ifndef ISTREAM_HELPER_H_
#define ISTREAM_HELPER_H_

#include <istream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Color.h"
#include "Math/Quaternion.h"
#include "Math/Matrix.h"

// Vector2‚Ì“Ç‚Ýž‚Ý
inline std::istream& operator >> (std::istream& in, Vector2& v) {
	return in >> v.x >> v.y;
}

// Vector3‚Ì“Ç‚Ýž‚Ý
inline std::istream& operator >> (std::istream& in, Vector3& v) {
	return in >> v.x >> v.y >> v.z;
}

// Vector4‚Ì“Ç‚Ýž‚Ý
inline std::istream& operator >> (std::istream& in, Color& c) {
	return in >> c.r >> c.g >> c.b >> c.a;
}

// Quaternion‚Ì“Ç‚Ýž‚Ý
inline std::istream& operator >> (std::istream& in, Quaternion& q) {
	return in >> q.x >> q.y >> q.z >> q.w;
}

// Matrix4‚Ì“Ç‚Ýž‚Ý
inline std::istream& operator >> (std::istream& in, Matrix& m) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			in >> m.m[i][j];
		}
	}
	return in;
}

template<typename T>
inline std::istream& operator >> (std::istream& in, std::vector<T>& vector) {
	std::size_t n = 0;
	in >> n;
	std::copy_n(std::istream_iterator<T>(in), n, std::back_inserter(vector));	
	return in;
}

#endif

