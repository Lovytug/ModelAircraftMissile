#include <type_traits>

template <typename State, typename Function>
inline State rk4_step(Function&& f, const State& y, double t, double h) {
    static_assert(std::is_invocable_v<Function, double, const State&>,
        "Function must be callable as f(t, y)");

    const auto k1 = f(t, y);
    const auto k2 = f(t + h / 2, y + h * k1 / 2);
    const auto k3 = f(t + h / 2, y + h * k2 / 2);
    const auto k4 = f(t + h, y + h * k3);

    return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}