#pragma once
#include <functional>
#include <memory>
#include <cmath>
#include <numeric>

template<typename T>
using u_ptr = std::unique_ptr<T>;

template<typename T>
using sh_ptr = std::shared_ptr<T>;

inline constexpr double M_PI = 3.14159265358979323846;