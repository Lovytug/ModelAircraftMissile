#include "MyDensityModelComputationRealisticPhisics.h"
#include "../../../../../../environment/simple_component/model_density/IDensityModel.h"

phis::MyDensityModelComputationRealisticPhisics::MyDensityModelComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyDensityModelComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<DensityModelComputationDynamicBundle>();

	bundle->add<double, const detail::IComputeModule&, double>(
		"density_func",
		[this](const detail::IComputeModule& computer, double h) -> double {
			return compute_density(computer, h);
		}
	);

	return bundle;
}

double phis::MyDensityModelComputationRealisticPhisics::compute_density(const detail::IComputeModule& computer, double h) const
{
	auto provider_density = computer.getProvider<env_dens::IDensityModel>();

	auto bundle_density = provider_density->getPhisicsFunc();

	auto density_func = bundle_density->call<double>("density_func");

	return density_func(*provider_density, h);
}