#include "MyNozzle.h"

noz::MyNozzle::MyNozzle(
	u_ptr<phis::IPhisicsModule> phisics,
	double critical_area_nozzle, double adiabatic_index,
	double V_effectiv, double temperature, 
	double R_g, std::string name
) :
	phisics(phisics),
	dyn_data(
		0.0,
		0.0,
		V_effectiv,
		temperature
	),
	stat_data(
		critical_area_nozzle,
		adiabatic_index,
		R_g,
		name
	)
{ }

void noz::MyNozzle::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& noz::MyNozzle::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& noz::MyNozzle::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> noz::MyNozzle::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}