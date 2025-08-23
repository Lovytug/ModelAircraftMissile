#include "NozzleComputationRealisticPhisics.h"
#include "../../../../rocket/engine/nozzle/INozzle.h"

phis::NozzleComputationRealisticPhisics::NozzleComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<DynamicBundle> phis::NozzleComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<NozzleComputationDynamicBundle>();

	bundle->add<double>(
		"mass_gaz_rate_func",
		[this](const comp::IComputeModule& computer, double pressure) -> double {
			return compute_mass_gaz_for_integarte(computer, pressure);
		}
	);

	bundle->add<double>(
		"F_thrust_func",
		[this](const comp::IComputeModule& computer, double pressure) -> double {
			return compute_F_thrust(computer, pressure);
		}
	);

	return bundle;
}

double phis::NozzleComputationRealisticPhisics::compute_mass_gaz_for_integarte(const comp::IComputeModule& computer, double pressure)
{
	auto provider_nozzle = computer.getProvider<noz::INozzle>();

	auto bundle_nozzle = provider_nozzle->getPhisicFunc();

	auto mass_gaz_rate_func = bundle_nozzle->call<double>("mass_gaz_rate_func");

	return mass_gaz_rate_func(provider_nozzle, pressure);
}

double phis::NozzleComputationRealisticPhisics::compute_F_thrust(const comp::IComputeModule& computer, double pressure)
{
	auto provider_nozzle = computer.getProvider<noz::INozzle>();

	auto bundle_nozzle = provider_nozzle->getPhisicFunc();

	auto F_thrust_func = bundle_nozzle->call<double>("F_thrust_func");

	return F_thrust_func(provider_nozzle, pressure);
}