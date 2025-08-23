#include "FuelModelComputationRealisticPhisics.h"
#include "../../../../rocket/engine/fuel/IFuelModel.h"
#include "../../../../rocket/engine/fuel/fuel_profile/IFuelProfile.h"

phis::FuelModelComputationRealisticPhisics::FuelModelComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<DynamicBundle> phis::FuelModelComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<FuelModelComputationDynamicBundle>();

	bundle->add<double>(
		"burn_rate_func",
		[this](const comp::IComputeModule& computer, double pressure) -> double {
			return compute_burn_rate_func_for_integrate(computer, pressure);
		}
	);

	bundle->add<double>(
		"mass_flow_rate_func",
		[this](const comp::IComputeModule& computer, double pressure) -> double {
			return compute_mass_flow_rate_for_integrate(computer, pressure);
		}
	);

	bundle->add<double>(
		"dr_inner_func",
		[this](const comp::IComputeModule& computer, double burn_rate) -> double {
			return compute_dr_inner_for_integrate(computer, burn_rate);
		}
	);

	return bundle;
}

double phis::FuelModelComputationRealisticPhisics::compute_burn_rate_func_for_integrate(const comp::IComputeModule& computer, double pressure)
{
	auto provider_fuel = computer.getProvider<fuel::IFuelModel>();

	auto bundle_fuel = provider_fuel->getPhisicFunc();

	auto burn_rate_func = bundle_fuel->call<double>("burn_rate_func");

	return burn_rate_func(provider_fuel, pressure);
}

double phis::FuelModelComputationRealisticPhisics::compute_mass_flow_rate_for_integrate(const comp::IComputeModule& computer, double pressure)
{
	auto provider_fuel = computer.getProvider<fuel::IFuelModel>();
	auto provider_profile_fuel = computer.getProvider<fuel::IFuelProfile>();

	auto bundle_fuel = provider_fuel->getPhisicFunc();
	auto bundle_profile = provider_profile_fuel->getPhisicFunc();

	auto mass_flow_rate_func = bundle_fuel->call<double>("mass_flow_rate_func");
	auto area_func = bundle_profile->call<double>("area_func");

	return mass_flow_rate_func(provider_fuel, pressure, area_func(provider_profile_fuel));
}

double phis::FuelModelComputationRealisticPhisics::compute_dr_inner_for_integrate(const comp::IComputeModule& computer, double burn_rate)
{
	auto provider_profile_fuel = computer.getProvider<fuel::IFuelProfile>();

	auto bundle_profile = provider_profile_fuel->getPhisicFunc();

	auto dr_inner_func = bundle_profile->call<double>("dr_inner_func");

	return dr_inner_func(provider_profile_fuel, burn_rate);

}