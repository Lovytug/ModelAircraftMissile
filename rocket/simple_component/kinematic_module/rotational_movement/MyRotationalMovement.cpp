#include "MyRotationalMovement.h"

kin_rot::MyRotationalMovement::MyRotationalMovement(
	u_ptr<phis::IPhisicsModule> phisics,
	double quaternion_orientation_w,
	double quaternion_orientation_x,
	double quaternion_orientation_y,
	double quaternion_orientation_z,
	double omega_x,
	double omega_y,
	double omega_z,
	std::string name
) :
	phisics(std::move(phisics)),
	dyn_data(
		quaternion_orientation_w,
		quaternion_orientation_x,
		quaternion_orientation_y,
		quaternion_orientation_z,
		omega_x,
		omega_y,
		omega_z
		),
	stat_data(
		name
	)
{
}

void kin_rot::MyRotationalMovement::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& kin_rot::MyRotationalMovement::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& kin_rot::MyRotationalMovement::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> kin_rot::MyRotationalMovement::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}