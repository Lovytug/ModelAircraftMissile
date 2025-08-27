#include "MyFuelModelComputationRealisticPhisics.h"
#include "../../../../../../../rocket/simple_component/engine/fuel/IFuelModel.h"
#include "../../../../../../../rocket/simple_component/engine/fuel/fuel_profile/IFuelProfile.h"

phis::MyFuelModelComputationRealisticPhisics::MyFuelModelComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyFuelModelComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<FuelModelComputationDynamicBundle>();

	bundle->add<double>(
		"burn_rate_func",
		[this](const detail::IComputeModule& computer, double pressure) -> double {
			return compute_burn_rate_func_for_integrate(computer, pressure);
		}
	);

	bundle->add<double>(
		"mass_flow_rate_func",
		[this](const detail::IComputeModule& computer, double pressure) -> double {
			return compute_mass_flow_rate_for_integrate(computer, pressure);
		}
	);

	bundle->add<double>(
		"dr_inner_func",
		[this](const detail::IComputeModule& computer, double burn_rate) -> double {
			return compute_dr_inner_for_integrate(computer, burn_rate);
		}
	);

	bundle->add<double>(
		"area_func",
		[this](const detail::IComputeModule& computer) -> double {
			return compute_area_func(computer);
		}
	);

	return bundle;
}

double phis::MyFuelModelComputationRealisticPhisics::compute_burn_rate_func_for_integrate(const detail::IComputeModule& computer, double pressure) const
{
	auto provider_fuel = computer.getProvider<fuel::IFuelModel>();

	auto bundle_fuel = provider_fuel->getPhisicsFunc();

	auto burn_rate_func = bundle_fuel->call<double>("burn_rate_func");

	return burn_rate_func(*provider_fuel, pressure);
}

double phis::MyFuelModelComputationRealisticPhisics::compute_area_func(const const detail::IComputeModule& computer) const
{
	auto provider_profile_fuel = computer.getProvider<fuel::IFuelProfile>();

	auto bundle_profile = provider_profile_fuel->getPhisicsFunc();

	auto area_func = bundle_profile->call<double>("area_func");

	return area_func(*provider_profile_fuel);
}


double phis::MyFuelModelComputationRealisticPhisics::compute_mass_flow_rate_for_integrate(const detail::IComputeModule& computer, double pressure) const
{
	auto provider_fuel = computer.getProvider<fuel::IFuelModel>();
	auto provider_profile_fuel = computer.getProvider<fuel::IFuelProfile>();

	auto bundle_fuel = provider_fuel->getPhisicsFunc();
	auto bundle_profile = provider_profile_fuel->getPhisicsFunc();

	auto mass_flow_rate_func = bundle_fuel->call<double>("mass_flow_rate_func");
	auto area_func = bundle_profile->call<double>("area_func");

	return mass_flow_rate_func(*provider_fuel, pressure, area_func(*provider_profile_fuel));
}

double phis::MyFuelModelComputationRealisticPhisics::compute_dr_inner_for_integrate(const detail::IComputeModule& computer, double burn_rate) const
{
	auto provider_profile_fuel = computer.getProvider<fuel::IFuelProfile>();

	auto bundle_profile = provider_profile_fuel->getPhisicsFunc();

	auto dr_inner_func = bundle_profile->call<double>("dr_inner_func");

	return dr_inner_func(*provider_profile_fuel, burn_rate);

}