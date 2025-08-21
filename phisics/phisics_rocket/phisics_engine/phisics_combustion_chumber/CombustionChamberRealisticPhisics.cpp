#include "CombustionChamberRealisticPhisics.h"

phis::CombustionChamberRealisticPhisics::CombustionChamberRealisticPhisics() {}

[[nodiscard]] double phis::CombustionChamberRealisticPhisics::compute_dP(const IComponent& combustion, double mass_fuel_rate, double mass_nozzle_rate) const noexcept
{
	auto state = combustion.getDynamicData();
	auto value = combustion.getStaticData().get<double>("R_g") * state.get<double>("temperature") / state.get<double>("V_cam");
	return value * (mass_fuel_rate - mass_nozzle_rate);
}

[[nodiscard]] std::unique_ptr<DynamicBundle> phis::CombustionChamberRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<NozzleDynamicBundle>();

	bundle->add<double, const IComponent&, double, double>(
		"dP_func",
		[this](const IComponent& combustion, double mass_fuel_rate, double mass_nozzle_rate) -> double {
			return compute_dP(combustion, mass_fuel_rate, mass_nozzle_rate);
		}
	);

	return bundle;
}