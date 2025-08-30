#include "MyRotationalMovementRealisticPhisics.h"

phis::MyRotationalMovementRealisticPhisics::MyRotationalMovementRealisticPhisics() {}

[[nodiscard]] double phis::MyRotationalMovementRealisticPhisics::compute_dquaternion_orientation_w(const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) const noexcept
{
	auto state = kinematik.getDynamicData();

	auto qx = state.get<double>("quaternion_orientation_x");
	auto qy = state.get<double>("quaternion_orientation_y");
	auto qz = state.get<double>("quaternion_orientation_z");

	return 0.5 * (-omega_x * qx - omega_y * qy - omega_z * qz);
}

[[nodiscard]] double phis::MyRotationalMovementRealisticPhisics::compute_dquaternion_orientation_x(const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) const noexcept
{
	auto state = kinematik.getDynamicData();

	auto qw = state.get<double>("quaternion_orientation_w");
	auto qy = state.get<double>("quaternion_orientation_y");
	auto qz = state.get<double>("quaternion_orientation_z");

	return 0.5 * (omega_x * qw + omega_z * qy - omega_y * qz);
}

[[nodiscard]] double phis::MyRotationalMovementRealisticPhisics::compute_dquaternion_orientation_y(const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) const noexcept
{
	auto state = kinematik.getDynamicData();

	auto qw = state.get<double>("quaternion_orientation_w");
	auto qx = state.get<double>("quaternion_orientation_x");
	auto qz = state.get<double>("quaternion_orientation_z");

	return 0.5 * (omega_y * qw - omega_z * qx + omega_x * qz);
}

[[nodiscard]] double phis::MyRotationalMovementRealisticPhisics::compute_dquaternion_orientation_z(const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) const noexcept
{
	auto state = kinematik.getDynamicData();

	auto qw = state.get<double>("quaternion_orientation_w");
	auto qx = state.get<double>("quaternion_orientation_x");
	auto qy = state.get<double>("quaternion_orientation_y");

	return 0.5 * (omega_z * qw + omega_y * qx - omega_x * qy);
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyRotationalMovementRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<RotationalMovementDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&, double, double, double>(
		"dquaternion_orientation_w_func",
		[this](const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) -> double {
			return compute_dquaternion_orientation_w(kinematik, omega_x, omega_y, omega_z);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double, double, double>(
		"dquaternion_orientation_x_func",
		[this](const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) -> double {
			return compute_dquaternion_orientation_x(kinematik, omega_x, omega_y, omega_z);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double, double, double>(
		"dquaternion_orientation_y_func",
		[this](const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) -> double {
			return compute_dquaternion_orientation_y(kinematik, omega_x, omega_y, omega_z);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double, double, double>(
		"dquaternion_orientation_z_func",
		[this](const detail::IDataProvider& kinematik, double omega_x, double omega_y, double omega_z) -> double {
			return compute_dquaternion_orientation_z(kinematik, omega_x, omega_y, omega_z);
		}
	);

	return bundle;
}