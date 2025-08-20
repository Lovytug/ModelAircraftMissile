#include "MyFuelModel.h"

fuel::MyFuelModel::MyFuelModel(
	IFuelProfile_uptr fuel_profile, IPhisicsModule_uptr phisics,
	double fuel_density, float a_boost, float a_sustain,
	float n_boost, float n_sustain, std::string name,

) : 
	profile(fuel_profile), phisics(phisics),
	dyn_data(0.0, 0.0, Mode::Boost, 0.0, 0.0),
	stat_data(fuel_density,
		a_boost, a_sustain,
		n_boost, n_sustain,
		name
	)
{
	
	profile->registerObserver(this);
}

void fuel::MyFuelModel::updateState(const MyFuelDynamicData& state)
{
	dyn_data = state;
}

DynamicDataType& fuel::MyFuelModel::getDynamicData() const noexcept
{
	return dyn_data;
}

StaticDataType& fuel::MyFuelModel::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscatd]] std::unique_ptr<phis::DynamicBundle> fuel::MyFuelModel::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle(); // надо расширить до возраения физики и профиля и самого топлива
}

void fuel::MyFuelModel::OnModeChanged(Mode newMode)
{
	dyn_data.set("currentMode", newMode);
}