#pragma once
#include <array>
#include <cstddef>
#include <utility>

template<std::size_t N>
struct StateBase {
    std::array<double, N> data{};

    StateBase() = default;

    StateBase operator+(const StateBase& other) const {
        StateBase result;
        for (std::size_t i = 0; i < N; ++i)
            result.data[i] = data[i] + other.data[i];
        return result;
    }
    StateBase operator-(const StateBase& other) const {
        StateBase result;
        for (std::size_t i = 0; i < N; ++i)
            result.data[i] = data[i] - other.data[i];

        return result;
    }
    StateBase operator*(double k) const {
        StateBase result;
        for (std::size_t i = 0; i < N; ++i)
            result.data[i] = data[i] * k;
        return result;
    }
    StateBase operator/(double k) const {
        StateBase result;
        for (std::size_t i = 0; i < N; ++i)
            result.data[i] = data[i] / k;
        return result;
    }
    StateBase& operator+=(const StateBase& other) {
        for (std::size_t i = 0; i < N; ++i)
            data[i] += other.data[i];
        return *this;
    }

    template<std::size_t I>
    double& get() { static_assert(I < N, "Index out of range"); return data[I]; }

    template<std::size_t I>
    const double& get() const { static_assert(I < N, "Index out of range"); return data[I]; }
};
