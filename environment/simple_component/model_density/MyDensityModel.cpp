#include "MyDensityModel.h"

env_dens::MyDensityModel::MyDensityModel(u_ptr<phis::IPhisicsModule> phisics)
	: phisics(phisics) {
}

void env_dens::MyDensityModel::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& env_dens::MyDensityModel::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& env_dens::MyDensityModel::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> env_dens::MyDensityModel::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}