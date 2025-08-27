#include "MyFuelModel.h"

fuel::MyFuelModel::MyFuelModel(
	u_ptr<phis::IPhisicsModule> phisics,
	double fuel_density, float a_boost, float a_sustain,
	float n_boost, float n_sustain, std::string name
) : 
	phisics(std::move(phisics)),
	dyn_data(0.0, 0.0, Mode::Boost),
	stat_data(fuel_density,
		a_boost, a_sustain,
		n_boost, n_sustain,
		name
	) {}

void fuel::MyFuelModel::updateState(const DynamicType& state)
{
	dyn_data = state;
}


[[nodiscard]] const detail::IComponent::DynamicType& fuel::MyFuelModel::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& fuel::MyFuelModel::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> fuel::MyFuelModel::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}