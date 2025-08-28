#include "MyCombustionChamberComputationRealisticPhisics.h"
#include "../../../../../../../rocket/simple_component/engine/combustion_chamber/ICombustionChamber.h"

phis::MyCombustionChamberComputationRealisticPhisics::MyCombustionChamberComputationRealisticPhisics() {}

[[nodiscard]] std::unique_ptr<mdt::DynamicBundle> phis::MyCombustionChamberComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<CombustionChamberComputationDynamicBundle>();

	bundle->add<double>(
		"dP_func",
		[this](const detail::IComputeModule& computer, double mass_fuel_rate, double mass_nozzle_rate) -> double {
			return compute_dP_for_integrate(computer, mass_fuel_rate, mass_nozzle_rate);
		}
	);

	return bundle;
}

double phis::MyCombustionChamberComputationRealisticPhisics::compute_dP_for_integrate(const detail::IComputeModule& computer, double mass_fuel_rate, double mass_nozzle_rate) const
{
	auto provider_chumber = computer.getProvider<chamb::ICombustionChamber>();

	auto bundle_chumber = provider_chumber->getPhisicsFunc();

	auto dP_func = bundle_chumber->call<double>("dP_func");

	return dP_func(*provider_chumber, mass_fuel_rate, mass_nozzle_rate);
}