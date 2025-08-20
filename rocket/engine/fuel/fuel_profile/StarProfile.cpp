#include "StarProfile.h"

fuel::StarProfile::StarProfile(
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
		L_boost.
		L_sustain,
		N,
		Amp,
		theta,
		name
	) { }


void fuel::StarProfile::updateState(const DynamicDataType& state)
{
	this->dyn_data = state;
}

[[nodiscard]] DynamicDataType& fuel::StarProfile::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] StaticDataType& fuel::StarProfile::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscatd]] std::unique_ptr<phis::DynamicBundle> fuel::StarProfile::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle();
}



// возможно удлаить все ниже. зачем оно нужно если я пполучаю состояния из вне и обновляю там же
void fuel::StarProfile::notifyObservers()
{
	for (auto& observer : this->observers)
	{
		observer->OnModeChanged(this->currentMode);
	}
}

void fuel::StarProfile::registerObserver(IModeObserver& observer)
{
	this->observers.push_back(observer);
}

void fuel::StarProfile::unregisterObserver(IModeObserver& observer)
{
	observers.erase(
		std::remove(observers.begin(), observers.end(), observer),
		observers.end()
	);
}

void fuel::StarProfile::setMode(Mode mode)
{
	if (this->currentMode != mode)
	{
		this->currentMode = mode;
		notifyObservers();
	}
}