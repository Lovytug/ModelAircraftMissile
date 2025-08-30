#include <cmath>
#include "Vector.h"

mml::Vector::Vector(size_t n) 
    : data(n, 0.0) {}

mml::Vector::Vector(std::initializer_list<double> init) 
    : data(init) {}

size_t mml::Vector::size() const {
    return data.size(); 
}

double mml::Vector::norm() const {
    return std::sqrt(dot(*this)); 
}

mml::Vector mml::Vector::normalized() const {
    double n = norm();
    if (n < 1e-12) throw std::runtime_error("It is impossible to normalize the null vector");
    return (*this) * (1.0 / n);
}

double mml::Vector::dot(const Vector& other) const {
    size_t n = size();
    if (n != other.size()) throw std::runtime_error("Size Vectors non");
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) sum += data[i] * other[i];
    return sum;
}