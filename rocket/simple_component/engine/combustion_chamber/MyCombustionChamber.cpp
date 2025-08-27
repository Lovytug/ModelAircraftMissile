#include "MyCombustionChamber.h"

chamb::MyCombustionChamber::MyCombustionChamber(
	u_ptr<phis::IPhisicsModule> phisics,
	double start_pressure, double V_cam,
	double R_g, std::string name
) :
	phisics(phisics),
	dyn_data(
		start_pressure,
		0.0,
		V_cam
	),
	stat_data(
		R_g,
		name
	)
{ }

void chamb::MyCombustionChamber::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& chamb::MyCombustionChamber::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& chamb::MyCombustionChamber::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscatd]] u_ptr<mdt::DynamicBundle> chamb::MyCombustionChamber::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}

