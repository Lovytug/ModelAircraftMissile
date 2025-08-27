#include "MyCombustionChamberRealisticPhisics.h"

phis::MyCombustionChamberRealisticPhisics::MyCombustionChamberRealisticPhisics() {}

[[nodiscard]] double phis::MyCombustionChamberRealisticPhisics::compute_dP(const detail::IDataProvider& combustion, double mass_fuel_rate, double mass_nozzle_rate) const noexcept
{
	auto state = combustion.getDynamicData();
	auto value = combustion.getStaticData().get<double>("R_g") * state.get<double>("temperature") / state.get<double>("V_cam");
	return value * (mass_fuel_rate - mass_nozzle_rate);
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyCombustionChamberRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<CombustionChamberDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double, double>(
		"dP_func",
		[this](const detail::IDataProvider& combustion, double mass_fuel_rate, double mass_nozzle_rate) -> double {
			return compute_dP(combustion, mass_fuel_rate, mass_nozzle_rate);
		}
	);

	return bundle;
}