#include "MyPressureModelRealisticPhisics.h"

phis::MyPressureModelRealisticPhisics::MyPressureModelRealisticPhisics() {}

[[nodiscard]] double phis::MyPressureModelRealisticPhisics::compute_pressure(const detail::IDataProvider& model, double h) const noexcept
{
	return 101325 * exp(-h / 7000.0);
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyPressureModelRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<PressureModelDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double>(
		"pressure_func",
		[this](const detail::IDataProvider& model, double h) -> double {
			return compute_pressure(model, h);
		}
	);

	return bundle;
}
