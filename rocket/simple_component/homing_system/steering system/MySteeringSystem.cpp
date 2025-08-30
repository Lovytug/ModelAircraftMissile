#include "MySteeringSystem.h"

steer::MySteeringSystem::MySteeringSystem(
	u_ptr<phis::IPhisicsModule> phisics,
	double tau, double delta_max_steering,
	double damping_coef, std::string name
) :
	phisics(std::move(phisics)),
	dyn_data(
		0.0,
		0.0,
		0.0
	),
	stat_data(
		tau,
		delta_max_steering,
		damping_coef,
		name
	)
{}

void steer::MySteeringSystem::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& steer::MySteeringSystem::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& steer::MySteeringSystem::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> steer::MySteeringSystem::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}