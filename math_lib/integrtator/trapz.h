#include <vector>
#include <cstddef>

// Аналог np.trapz(y, x): численное интегрирование методом трапеций
[[nodiscard]] inline double trapz(const std::vector<double>& y, const std::vector<double>& x) {
    if (y.size() != x.size() || y.size() < 2) {
        return 0.0;
    }

    double integral = 0.0;
    for (size_t i = 1; i < x.size(); ++i) {
        double h = x[i] - x[i - 1];
        double avg = (y[i] + y[i - 1]) / 2.0;
        integral += avg * h;
    }
    return integral;
}