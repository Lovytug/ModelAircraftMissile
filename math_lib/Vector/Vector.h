#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

namespace mml
{
    class Vector
    {
    private:
        std::vector<double> data;

    public:
        Vector() = default;
        explicit Vector(size_t n);
        Vector(std::initializer_list<double> init);

        double norm() const;
        double dot(const Vector& other) const;
        Vector normalized() const;
        size_t size() const;

        double& operator[](size_t i) { return data.at(i); }
        const double& operator[](size_t i) const { return data.at(i); }

        Vector operator+(const Vector& other) const {
            size_t n = size();
            if (n != other.size()) throw std::runtime_error("Размеры векторов не совпадают");
            Vector result(n);
            for (size_t i = 0; i < n; ++i) result[i] = data[i] + other[i];
            return result;
        }

        Vector operator-(const Vector& other) const {
            size_t n = size();
            if (n != other.size()) throw std::runtime_error("Размеры векторов не совпадают");

            Vector result(n);
            for (size_t i = 0; i < n; ++i) result[i] = data[i] - other[i];
            return result;
        }

        Vector operator*(double k) const {
            size_t n = size();
            Vector result(n);
            for (size_t i = 0; i < n; ++i) result[i] = data[i] * k;
            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
            os << "[ ";
            for (double val : v.data) os << val << " ";
            os << "]";
            return os;
        }
    };
}
