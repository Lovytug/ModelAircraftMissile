#pragma once
#include <functional>
#include <memory>
#include <cmath>
#include <numeric>

template<typename T>
using u_ptr<T> = std::unique_ptr<T>

template<typename T>
using sh_ptr<T> = std::shared_ptr<T>

inline constexpr M_PI = std::acos(-1);