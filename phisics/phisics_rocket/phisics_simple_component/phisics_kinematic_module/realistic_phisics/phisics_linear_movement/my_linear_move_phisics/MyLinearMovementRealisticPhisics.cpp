#include "MyLinearMovementRealisticPhisics.h"

phis::MyLinearMovementRealisticPhisics::MyLinearMovementRealisticPhisics() {}

[[nodiscard]] double phis::MyLinearMovementRealisticPhisics::compute_pos_x(const detail::IDataProvider& kinematik, double vel_x) const noexcept
{
	return vel_x;
}

[[nodiscard]] double phis::MyLinearMovementRealisticPhisics::compute_pos_y(const detail::IDataProvider& kinematik, double vel_y) const noexcept
{
	return vel_y;
}

[[nodiscard]] double phis::MyLinearMovementRealisticPhisics::compute_pos_z(const detail::IDataProvider& kinematik, double vel_z) const noexcept
{
	return vel_z;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyLinearMovementRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<LinearMovementDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double>(
		"pos_x_func",
		[this](const detail::IDataProvider& kinematik, double vel_x) -> double {
			return compute_pos_x(kinematik, vel_x);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double>(
		"pos_y_func",
		[this](const detail::IDataProvider& kinematik, double vel_y) -> double {
			return compute_pos_y(kinematik, vel_y);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double>(
		"pos_y_func",
		[this](const detail::IDataProvider& kinematik, double vel_z) -> double {
			return compute_pos_z(kinematik, vel_z);
		}
	);

	return bundle;
}