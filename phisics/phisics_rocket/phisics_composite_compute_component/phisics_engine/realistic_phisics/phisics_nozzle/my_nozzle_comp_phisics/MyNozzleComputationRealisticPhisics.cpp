#include "MyNozzleComputationRealisticPhisics.h"
#include "../../../../../../../rocket/simple_component/engine/nozzle/INozzle.h"

phis::MyNozzleComputationRealisticPhisics::MyNozzleComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyNozzleComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<NozzleComputationDynamicBundle>();

	bundle->add<double>(
		"mass_gaze_rate_func",
		[this](const detail::IComputeModule& computer, double pressure) -> double {
			return compute_mass_gaz_for_integarte(computer, pressure);
		}
	);

	bundle->add<double>(
		"F_thrust_func",
		[this](const detail::IComputeModule& computer, double pressure) -> double {
			return compute_F_thrust(computer, pressure);
		}
	);

	return bundle;
}

double phis::MyNozzleComputationRealisticPhisics::compute_mass_gaz_for_integarte(const detail::IComputeModule& computer, double pressure) const
{
	auto provider_nozzle = computer.getProvider<noz::INozzle>();

	auto bundle_nozzle = provider_nozzle->getPhisicsFunc();

	auto mass_gaz_rate_func = bundle_nozzle->call<double>("mass_gaze_rate_func");

	return mass_gaz_rate_func(provider_nozzle, pressure);
}

double phis::MyNozzleComputationRealisticPhisics::compute_F_thrust(const detail::IComputeModule& computer, double pressure) const
{
	auto provider_nozzle = computer.getProvider<noz::INozzle>();

	auto bundle_nozzle = provider_nozzle->getPhisicsFunc();

	auto F_thrust_func = bundle_nozzle->call<double>("F_thrust_func");

	return F_thrust_func(provider_nozzle, pressure);
}