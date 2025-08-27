#include <memory>
#include <cmath>
#include "../../../../../../../rocket/simple_component/engine/fuel/IFuelModel.h"
#include "MyFuelModelRealisticPhisics.h"

phis::MyFuelModelRealisticPhisics::MyFuelModelRealisticPhisics() {}

double phis::MyFuelModelRealisticPhisics::compute_burn_rate(const detail::IDataProvider& fuel, double pressure) const
{
	auto state = fuel.getStaticData();
	if (fuel.getDynamicData().get<fuel::Mode>("currentMode") == fuel::Mode::Boost)
		return state.get<float>("a_boost") * std::pow(pressure, state.get<float>("n_boost"));
	else
		return state.get<float>("a_sustain") * std::pow(pressure, state.get<float>("n_sustain"));
}

double phis::MyFuelModelRealisticPhisics::compute_mass_flow_rate(const detail::IDataProvider& fuel, double pressure, double area) const
{
	return fuel.getStaticData().get<double>("fuel_density") * compute_burn_rate(fuel, pressure) * area;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyFuelModelRealisticPhisics::getDynamicBundle() const noexcept
{
	auto bundle = std::make_unique<FuelModelDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double>(
		"burn_rate_func",
		[this](const detail::IDataProvider& fuel, double pressure) -> double {
			return compute_burn_rate(fuel, pressure);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double, double>(
		"mass_flow_rate_func",
		[this](const detail::IDataProvider& fuel, double pressure, double area) -> double {
			return compute_mass_flow_rate(fuel, pressure, area);
		}
	);

	return bundle;
}