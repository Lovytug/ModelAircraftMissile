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
	stat_dyn(
		R_g,
		name
	)
{ }

void chamb::MyCombustionChamber::updateState(const MyCombustionChamberDynamicData& state)
{
	dyn_data = state;
}

DynamicDataType& chamb::MyCombustionChamber::getDynamicData() const noexcept
{
	return dyn_data;
}

StaticDataType& chamb::MyCombustionChamber::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscatd]] u_ptr<phis::DynamicBundle> chamb::MyCombustionChamber::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle();
}

