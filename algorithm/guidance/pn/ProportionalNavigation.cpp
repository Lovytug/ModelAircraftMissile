#include <cmath>
#include "ProportionalNavigation.h"

Vec3d alg::ProportionalNavigation::call_algorithm(Vec3d R, Vec3d Vr) const noexcept
{
    return proportional_navigation(std::move(R), std::move(Vr));
}

double alg::ProportionalNavigation::dot(const Vec3d& a, const Vec3d& b) const noexcept {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

Vec3d alg::ProportionalNavigation::cross(const Vec3d& a, const Vec3d& b) const noexcept {
    return {
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    };
}

double alg::ProportionalNavigation::norm(const Vec3d& v) const noexcept {
    return std::sqrt(dot(v, v));
}

Vec3d alg::ProportionalNavigation::normalize(const Vec3d& v) const noexcept {
    double n = norm(v);
    return (n > 1e-9) ? (v / n) : Vec3d{ 0,0,0 };
}