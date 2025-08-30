#include "MyPressureModel.h"

env_pres::MyPressureModel::MyPressureModel(u_ptr<phis::IPhisicsModule> phisics)
: phisics(phisics) {}

void env_pres::MyPressureModel::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& env_pres::MyPressureModel::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& env_pres::MyPressureModel::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> env_pres::MyPressureModel::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}