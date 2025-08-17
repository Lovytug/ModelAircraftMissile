#include "MyFuelModel.h"

fuel::MyFuelModel::MyFuelModel(IFuelProfile& fuel_profile, IDataProvider& sensor,
	double fuel_density, float a_boost, float a_sustain,
	float n_boost, float n_sustain, std::string name) :
	profile(fuel_profile), sensor_pressure(sensor), fuel_density(fuel_density),
	a_boost(a_boost), a_sustain(a_sustain), n_boost(n_boost), n_sustain(n_sustain),
	name(name), burn_rate(0.0), mass_flow_rate(0.0), time(0.0) {

	profile.registerObserver(this);
}

void  fuel::MyFuelModel::update(double dt)
{
	updateTine(dt);

	auto burn_rate_func = [this]() -> double {
		return compute_burn_rate();
		};

	profile.update(burn_rate_func, dt)

	burn_rate = burn_rate_func();

	mass_flow_rate= fuel_density * burn_rate * profile.getBurnArea()
}

[[nodiscard]] double fuel::MyFuelModel::getMassFlowRate() const
{
	return this->mass_flow_rate;
}

[[nodiscard]] std::string fuel::MyFuelModel::getName() const
{
	return this->name;
}

[[nodiscard]] std::vector<double> fuel::MyFuelModel::getVectorState() const
{

}


inline void fuel::MyFuelModel::updateTime(double dt)
{
	this->time += dt;
}

[[nodiscard]] double fuel::MyFuelModel::compute_burn_rate()
{
	double pressure = sensor_pressore.readValue();

	if (currentMode == Mode::Boost)
		return a_boost * std::pow(pressure, n_boost);
	else
		return a_sustain * std::pow(pressure, n_sustain);
}

void fuel::MyFuelModel::OnModeChanged(Mode newMode)
{
	this->currentMode = newMode;
}