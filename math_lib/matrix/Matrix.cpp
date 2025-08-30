#include <cmath>
#include "Matrix.h"

mml::Matrix::Matrix() : nrows(0), ncols(0) {}

mml::Matrix::Matrix(size_t rows, size_t cols) : nrows(rows), ncols(cols), data(rows* cols, 0.0) {}

mml::Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init) 
{
    nrows = init.size();
    ncols = init.begin()->size();
    data.reserve(nrows * ncols);

    for (auto& row : init) {
        if (row.size() != ncols) throw std::runtime_error("Uneven lines in initialization");
        for (double val : row) data.push_back(val);
    }
}

size_t mml::Matrix::rows() const { 
    return nrows; 
}

size_t mml::Matrix::cols() const { 
    return ncols; 
}

mml::Matrix mml::Matrix::transpose() const 
{
    Matrix result(ncols, nrows);
    for (size_t i = 0; i < nrows; ++i)
        for (size_t j = 0; j < ncols; ++j)
            result(j, i) = (*this)(i, j);
    return result;
}

void mml::Matrix::LU(Matrix& L, Matrix& U, std::vector<size_t>& P) const 
{
    if (nrows != ncols) throw std::runtime_error("The matrix must be square");
    size_t n = nrows;
    L = Matrix(n, n);
    U = *this;
    P.resize(n);
    for (size_t i = 0;i < n;++i) P[i] = i;

    for (size_t k = 0;k < n;++k) {
        // pivot
        double maxA = 0.0;
        size_t imax = k;
        for (size_t i = k;i < n;++i) {
            double val = std::fabs(U(P[i], k));
            if (val > maxA) { maxA = val; imax = i; }
        }
        if (maxA < 1e-12) throw std::runtime_error("The matrix is degenerate");

        if (imax != k) std::swap(P[k], P[imax]);

        for (size_t i = k + 1;i < n;++i) {
            double f = U(P[i], k) / U(P[k], k);
            U(P[i], k) = f;
            for (size_t j = k + 1;j < n;++j)
                U(P[i], j) -= f * U(P[k], j);
        }
    }

    // Заполняем L и U
    for (size_t i = 0;i < n;++i) {
        for (size_t j = 0;j < n;++j) {
            if (i > j) {
                L(i, j) = U(P[i], j);
                U(i, j) = 0.0;
            }
            else if (i == j) {
                L(i, j) = 1.0;
            }
            else {

                L(i, j) = 0.0;
            }
        }
        for (size_t j = i;j < n;++j)
            U(i, j) = U(P[i], j);
    }
}

double mml::Matrix::determinant() const 
{
    if (nrows != ncols) throw std::runtime_error("The matrix must be square");
    Matrix L, U;
    std::vector<size_t> P;
    LU(L, U, P);
    double det = 1.0;
    int parity = 0;
    for (size_t i = 0;i < nrows;++i) {
        det *= U(i, i);
        if (P[i] != i) parity++;
    }
    if (parity % 2) det = -det;
    return det;
}

mml::Matrix mml::Matrix::inverse() const 
{
    if (nrows != ncols) throw std::runtime_error("The matrix must be square");
    size_t n = nrows;
    Matrix L, U;
    std::vector<size_t> P;

    LU(L, U, P);

    Matrix inv(n, n);
    for (size_t col = 0;col < n;++col) {
        // решаем L*y = e(col)
        std::vector<double> y(n, 0.0);
        for (size_t i = 0;i < n;++i) {
            y[i] = (P[i] == col) ? 1.0 : 0.0;
            for (size_t j = 0;j < i;++j)
                y[i] -= L(i, j) * y[j];
        }
        // решаем U*x = y
        std::vector<double> x(n, 0.0);
        for (int i = n - 1;i >= 0;--i) {
            x[i] = y[i];
            for (size_t j = i + 1;j < n;++j)
                x[i] -= U(i, j) * x[j];
            x[i] /= U(i, i);
        }
        for (size_t i = 0;i < n;++i)
            inv(i, col) = x[i];
    }
    return inv;
}