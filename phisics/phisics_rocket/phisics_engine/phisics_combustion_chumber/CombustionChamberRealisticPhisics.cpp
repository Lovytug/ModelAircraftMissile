#include "CombustionChamberRealisticPhisics.h"

phis::CombustionChamberRealisticPhisics::CombustionChamberRealisticPhisics() {}

[[nodiscard]] double phis::CombustionChamberRealisticPhisics::compute_dp(const ICombustionChamber& combustion, double mass_fuel_rate, double mass_nozzle_rate) const noexcept
{
	auto state = combustion.getDynamicData();
	auto value = combustion.getStaticData().get<double>("R_g") * state.get<double>("temperature") / state.get<double>("V_cam");
	return value * (mass_fuel_rate - mass_nozzle_rate);
}

[[nodiscard]] std::unique_ptr<DynamicBundle> phis::CombustionChamberRealisticPhisics::getDynamicBundle() const
{
	return {
		[this](const auto& combustion, double mass_fuel_rate, double mass_nozzle_rate) {
			return compute_mass_flow_rate(combustion, mass_fuel_rate, mass_nozzle_rate);
		};
	};
}