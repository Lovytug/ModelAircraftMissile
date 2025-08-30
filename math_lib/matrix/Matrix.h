#include <iostream>
#include <vector>
#include <stdexcept>
#include "../Vector/Vector.h"

namespace mml
{
    class Vector;

    class Matrix 
    {
    private:
        size_t nrows, ncols;
        std::vector<double> data;

        size_t idx(size_t i, size_t j) const { return i * ncols + j; }

    public:
        Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(std::initializer_list<std::initializer_list<double>> init);

        size_t rows() const;
        size_t cols() const;

        double& operator()(size_t i, size_t j) { return data.at(idx(i, j)); }
        const double& operator()(size_t i, size_t j) const { return data.at(idx(i, j)); }

        Matrix transpose() const;

        // LU-разложение с перестановкой строк
        void LU(Matrix& L, Matrix& U, std::vector<size_t>& P) const;

        double determinant() const;

        Matrix inverse() const;

        Matrix operator*(const Matrix& other) const {
            if (ncols != other.nrows) throw std::runtime_error("Ќесовместимые размеры матриц");
            Matrix result(nrows, other.ncols);
            for (size_t i = 0; i < nrows; ++i)
                for (size_t j = 0; j < other.ncols; ++j) {
                    double sum = 0.0;

                    for (size_t k = 0; k < ncols; ++k)
                        sum += (*this)(i, k) * other(k, j);
                    result(i, j) = sum;
                }
            return result;
        }

        Vector operator*(const Vector& v) const {
            if (ncols != v.size()) throw std::runtime_error("–азмеры матрицы и вектора не совпадают");
            Vector result(nrows);
            for (size_t i = 0; i < nrows; ++i) {
                double sum = 0.0;
                for (size_t j = 0; j < ncols; ++j) sum += (*this)(i, j) * v[j];
                result[i] = sum;
            }
            return result;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
            for (size_t i = 0; i < m.nrows; ++i) {
                os << "[ ";
                for (size_t j = 0; j < m.ncols; ++j)

                    os << m(i, j) << " ";
                os << "]\n";
            }
            return os;
        }
    };
}