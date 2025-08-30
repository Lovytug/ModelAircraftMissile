#include "MyLinearMovement.h"

kin_lin::MyLinearMovement::MyLinearMovement(
	u_ptr<phis::IPhisicsModule> phisics,
	double pos_x, double pos_y, double pos_z,
	std::string name
) :
	phisics(std::move(phisics)),
	dyn_data(
		pos_x,
		pos_y,
		pos_z,
	),
	stat_data(
		name
	)
{ }

void kin_lin::MyLinearMovement::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& kin_lin::MyLinearMovement::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& kin_lin::MyLinearMovement::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> kin_lin::MyLinearMovement::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}