#include "MySteeringSystemRealisticPhisics.h"

phis::MySteeringSystemRealisitcPhisics::MySteeringSystemRealisitcPhisics() {}

[[nodiscard]] double phis::MySteeringSystemRealisitcPhisics::compute_ddeltta(const detail::IDataProvider& steer) const noexcept
{
	return steer.getDynamicData().get<double>("zeta");
}

[[nodiscard]] double phis::MySteeringSystemRealisitcPhisics::compute_dzeta(const detail::IDataProvider& steer, double cmd) const noexcept
{
	auto state = steer.getStaticData();
	double omega_n = 1.0 / state.get<double>("tau");
	return pow(omega_n, 2) * (cmd - steer.getDynamicData().get<double>("delta_steering") -
		2.0 * state.get<double>("damping_coef") * omega_n * steer.getDynamicData().get<double>("zeta_steering");
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MySteeringSystemRealisitcPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<SteeringSystemDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&>(
		"ddelta_func",
		[this](const detail::IDataProvider& steer) -> double {
			return compute_ddeltta(steer);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double>(
		"dzeta_func",
		[this](const detail::IDataProvider& nozzle, double cmd) -> double {
			return compute_dzeta(nozzle, cmd);
		}
	);

	return bundle;
}
