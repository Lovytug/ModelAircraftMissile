#include "MyEnvironmentModelComputationRealisticPhisics.h"
#include "../../../../../../environment/composite_compute_component/model_density/IDensityModelComputation.h"
#include "../../../../../../environment/composite_compute_component/model_pressure/IPressureModelComputation.h"

phis::MyEnvironmentModelComputationRealisticPhisics::MyEnvironmentModelComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyEnvironmentModelComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<EnvironmentModelComputationDynamicBundle>();

	bundle->add<double, const detail::IComputeModule&, double>(
		"environment_func",
		[this](const detail::IComputeModule& computer, double h) -> detail::IComputeModule::DynamicType {
			return compute_environment(computer, h);
		}
	);

	return bundle;
}

detail::IComputeModule::DynamicType phis::MyEnvironmentModelComputationRealisticPhisics::compute_environment(const detail::IComputeModule & computer, double h) const
{
	auto provider_pressure = computer.getProvider<env_comp::IPressureModelComputation>();
	auto provider_density = computer.getProvider<env_comp::IDensityModelComputation>();

	auto bundle_pressure = provider_pressure->getPhisicsFunc();
	auto bundle_density = provider_density->getPhisicsFunc();

	auto pressure_func = bundle_pressure->call<double>("pressure_func");
	auto density_func = bundle_density->call<double>("density_func");


	detail::IComputeModule::DynamicType result;
	result.set<env_comp::IPressureModelComputation>("pressure", pressure_func(*provider_pressure, h));
	result.set<env_comp::IDensityModelComputation>("density", density_func(*provider_density, h));

	return result;
}