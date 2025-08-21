#include "FuelModelRealisticPhisics.h"

phis::FuelModelRealisticPhisics::FuelModelRealisticPhisics() 
	: {}


double phis::FuelModelRealisticPhisics::compute_burn_rate(const IComponent& fuel, double pressure) const
{
	auto state = fuel.getStaticData();
	if (fuel.getDynamicData().get<fuel::Mode>("currentMode") == fuel::Mode::Boost)
		return state.get<float>("a_boost") * std::pow(pressure, state.get<float>("n_boost"));
	else
		return state.get<float>("a_sustain") * std::pow(pressure, state.get<float>("n_sustain"));
}


double phis::FuelModelRealisticPhisics::compute_mass_flow_rate(const IComponent& fuel, double pressure) const
{
	auto state = fuel.getStaticData();
	return state.get<double>("fuel_density") * compute_burn_rate(fuel, pressure) * fuel.getDynamicData().get<float>("area");
}


[[nodiscard]] std::unique_ptr<DynamicBundle> phis::FuelModelRealisticPhisics::getDynamicBundle() const noexcept
{
	auto bundle = std::make_unique<FuelModelDynamicBundle>();

	bundle->add<double, const IComponent&, double>(
		"bern_rate_func",
		[this](const IComponent& fuel, double pressure) -> double {
			return compute_burn_rate(fuel, pressure);
		}
	);

	bundle->add<double, const IComponent&, double>(
		"mass_flow_rate_func",
		[this](const IComponent& fuel, double pressure) -> double {
			return compute_mass_flow_rate(fuel, pressure);
		}
	);

	return bundle;
}