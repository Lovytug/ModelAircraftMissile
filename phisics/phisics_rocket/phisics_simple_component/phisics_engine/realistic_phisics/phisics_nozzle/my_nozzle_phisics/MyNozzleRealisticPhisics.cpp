#include "MyNozzleRealisticPhisics.h"

phis::MyNozzleRealisticPhisics::MyNozzleRealisticPhisics() {}

[[nodiscard]] double phis::MyNozzleRealisticPhisics::compute_mass_gaz_rate(const detail::IDataProvider& nozzle, double pressure) const noexcept
{
	auto state = nozzle.getStaticData();

	auto crit_area = state.get<double>("critical_area_nozzle");
	auto adiabatic = state.get<double>("adiabatic_index");
	auto R_g = state.get<double>("R_g");
	auto T = nozzle.getDynamicData().get<double>("temperature");

	auto P = get_P(pressure);
	auto P_crit = get_P_crit(adiabatic);
	if (P <= P_crit)
		return pressure * crit_area *
			sqrt(adiabatic / (R_g * T)) *
			std::pow(2.0 / (adiabatic + 1.0), (adiabatic + 1.0) / (2.0 * (adiabatic + 1.0)));
	else
		return pressure * crit_area *
		sqrt( ( (2.0 * adiabatic) / (R_g * T * (adiabatic + 1.0) ) ) * 
			(std::pow(get_P(pressure), 2.0 / adiabatic) - 
				std::pow(get_P(pressure), (adiabatic + 1.0) / adiabatic) ) );
}

[[nodiscard]] double phis::MyNozzleRealisticPhisics::compute_F_thrust(const detail::IDataProvider& nozzle, double pressure) const noexcept
{
	return compute_mass_gaz_rate(nozzle, pressure) * nozzle.getDynamicData().get<double>("V_effectiv") +
		(pressure - const_P_a) * nozzle.getStaticData().get<double>("critical_area_nozzle");
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyNozzleRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<NozzleDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double>(
		"mass_gaze_rate_func",
		[this](const detail::IDataProvider& nozzle, double pressure) -> double {
			return compute_mass_gaz_rate(nozzle, pressure);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double>(
		"F_thrust_func",
		[this](const detail::IDataProvider& nozzle, double pressure) -> double {
			return compute_F_thrust(nozzle, pressure);
		}
	);

	return bundle;
}


[[nodiscard]] inline double phis::MyNozzleRealisticPhisics::get_P(double pressure) const noexcept
{
	return pressure / const_P_a;
}

[[nodiscard]] inline double phis::MyNozzleRealisticPhisics::get_P_crit(double adiabatic) const noexcept
{
	return std::pow(2.0 / (adiabatic + 1), adiabatic / (adiabatic - 1.0));
}