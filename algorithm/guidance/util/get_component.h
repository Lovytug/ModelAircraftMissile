#pragma once
#include <cstddef>

template<typename V>
inline auto get_component(const V& v, std::size_t i) -> decltype(v[i]) {
	return v[i];
}