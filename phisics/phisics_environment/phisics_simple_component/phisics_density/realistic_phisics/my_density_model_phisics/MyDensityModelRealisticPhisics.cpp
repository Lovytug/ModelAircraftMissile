#include "MyDensityModelRealisticPhisics.h"

phis::MyDensityModelRealisticPhisics::MyDensityModelRealisticPhisics() {}

[[nodiscard]] double phis::MyDensityModelRealisticPhisics::compute_density(const detail::IDataProvider& model, double h) const noexcept
{
	return 1.225 * exp(-h / 8000.0);
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyDensityModelRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<DensityModelDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double>(
		"density_func",
		[this](const detail::IDataProvider& model, double h) -> double {
			return compute_density(model, h);
		}
	);

	return bundle;
}