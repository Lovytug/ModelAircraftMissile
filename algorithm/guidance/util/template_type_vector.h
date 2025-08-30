#pragma once
#include <array>
#include "get_component.h"

using Vec3d = std::array<double, 3>;

template<typename V>
inline Vec3d to_array3(const V& v) {
	return {
		static_cast<double>(get_component(v, 0)),
		static_cast<double>(get_component(v, 1)),
		static_cast<double>(get_component(v, 2))
	};
}

inline Vec3d operator+(const Vec3d& a, const Vec3d& b) {
	return { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
}
inline Vec3d operator-(const Vec3d& a, const Vec3d& b) {
	return { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
}
inline Vec3d operator*(double k, const Vec3d& v) {
	return { k * v[0], k * v[1], k * v[2] };
}
inline Vec3d operator/(const Vec3d& v, double k) {
	return { v[0] / k, v[1] / k, v[2] / k };
}

