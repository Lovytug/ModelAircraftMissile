#include <string>
#include <vector>
#include <cmath>
#include "runge_kutta.h"
#include "trapz.h"
#include "StarProfile.h"

fuel::StarProfile::StarProfile(
	u_ptr<phis::IPhisicsModule> phisics,
	double R_o, double r_inner, double L_boost, double L_sustain,
	short N, double amp, double theta, std::string name
) :
	dyn_data(
		0.0,
		r_inner,
		Mode::Boost
	),
	stat_data(
		R_o,
		L_boost,
		L_sustain,
		N,
		amp,
		theta,
		name
	) { }


void fuel::StarProfile::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& fuel::StarProfile::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& fuel::StarProfile::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> fuel::StarProfile::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle();
}