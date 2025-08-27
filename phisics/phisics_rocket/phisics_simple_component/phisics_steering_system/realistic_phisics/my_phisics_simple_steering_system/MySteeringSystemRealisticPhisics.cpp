#include "MySteeringSystemRealisticPhisics.h"

phis::MySteeringSystemRealisitcPhisics::MySteeringSystemRealisitcPhisics() {}

[[nodiscard]] double phis::MySteeringSystemRealisitcPhisics::compute_ddeltta(const detail::IDataProvider& steer) const noexcept
{
	return steer.getDynamicData().get<double>("zeta");
}

[[nodiscard]] double phis::MySteeringSystemRealisitcPhisics::compute_dzeta(const detail::IDataProvider& nozzle, double cmd) const noexcept
{

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


[[nodiscard]] inline double phis::NozzleRealisticPhisics::get_P(double pressure) const noexcept
{
	return pressure / const_P_a;
}

[[nodiscard]] inline double phis::NozzleRealisticPhisics::get_P_crit(double adiabatic) const noexcept
{
	return std::pow(2.0 / (adiabatic + 1), adiabatic / (adiabatic - 1.0));
}