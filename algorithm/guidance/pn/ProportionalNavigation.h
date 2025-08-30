#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../../IBaseAlgorithm.h"

namespace alg
{
    class ProportionalNavigation final : public IBaseAlgorithm
    {
    public:
        ProportionalNavigation(short N);

        Vec3d call_algorithm(Vec3d R, Vec3d Vr) const noexcept override;

    private:
        [[nodiscard]] double dot(const Vec3d& a, const Vec3d& b) const noexcept;
        [[nodiscard]] Vec3d cross(const Vec3d& a, const Vec3d& b) const noexcept;
        [[nodiscard]] double norm(const Vec3d& v) const noexcept;
        [[nodiscard]] Vec3d normalize(const Vec3d& v) const noexcept;

        [[nodiscard]] Vec3d proportional_navigation(const Vec3d& R_, const Vec3d& Vr_) const noexcept;

    private:
        short N;
    };

    [[nodiscard]] Vec3d ProportionalNavigation::proportional_navigation(const Vec3d& R_, const Vec3d& Vr_) const noexcept {
        double Rnorm = norm(R_);
        if (Rnorm < 1e-9) return { 0,0,0 };


        Vec3d u = normalize(R_);
        double Vc = -dot(R_, Vr_) / Rnorm;
        Vec3d lambda_dot = cross(R_, Vr_) / (Rnorm * Rnorm);
        Vec3d am = N * Vc * cross(lambda_dot, u);

        return am;
    }
}
