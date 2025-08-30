#include "MyPressureModelComputationRealisticPhisics.h"
#include "../../../../../../environment/simple_component/model_pressure/IPressureModel.h"

phis::MyPressureModelComputationRealisticPhisics::MyPressureModelComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyPressureModelComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<PressureModelComputationDynamicBundle>();

	bundle->add<double, const detail::IComputeModule&, double>(
		"pressure_func",
		[this](const detail::IComputeModule& computer, double h) -> double {
			return compute_pressure(computer, h);
		}
	);

	return bundle;
}

double phis::MyPressureModelComputationRealisticPhisics::compute_pressure(const detail::IComputeModule& computer, double h) const
{
	auto provider_pressure = computer.getProvider<env_pres::IPressureModel>();

	auto bundle_pressure = provider_pressure->getPhisicsFunc();

	auto pressure_func = bundle_pressure->call<double>("pressure_func");

	return pressure_func(*provider_pressure, h);
}