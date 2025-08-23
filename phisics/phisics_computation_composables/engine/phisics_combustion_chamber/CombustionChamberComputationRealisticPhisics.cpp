#include "CombustionChamberComputationRealisticPhisics.h"
#include "../../../../rocket/engine/combustion_chamber/ICombustionChamber.h"

phis::CombustionChamberComputationRealisticPhisics::CombustionChamberComputationRealisticPhisics() {}

[[nodiscard]] std::unique_ptr<DynamicBundle> phis::CombustionChamberComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<CombustionChamberComputationDynamicBundle>();

	bundle->add<double>(
		"dP_func",
		[this](const comp::IComputeModule& computer, double mass_fuel_rate, double mass_nozzle_rate) -> double {
			return compute_dP_for_integrate(computer, mass_fuel_rate, mass_nozzle_rate);
		}
	);

	return bundle;
}

double phis::CombustionChamberComputationRealisticPhisics::compute_dP_for_integrate(const comp::IComputeModule& computer, double mass_fuel_rate, double mass_nozzle_rate)
{
	auto provider_chumber = computer.getProvider<chamb::ICombustionChamber>();

	auto bundle_chumber = provider_chumber->getPhisicFunc();

	auto dP_func = bundle_chumber->call<double>("dP_func");

	return dP_func(provider_chumber, mass_fuel_rate, mass_nozzle_rate);
}