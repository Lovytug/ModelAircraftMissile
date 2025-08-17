#include "StarProfile.h"

fuel::StarProfile::StarProfile(
	double R_o, double R_i_0, double L_boost, double L_sustain,
	double N, double amp, double theta, std::string name
) :
	R_o(R_o), R_inner(R_i_0), L_boost(L_boost), L_sustain(L_sustain),
	N(N), Amp(amp), theta(theta), name(name), time(0.0), area(0.0) { 
	
	this->area = compute_area();
}

void fuel::StarProfile::update(BurnRateFunction burn_rate_func, double dt)
{
	updateTime(dt);

	[this, &currentMode]() {
		if (R_inner >= R_o) setMode(Mode::Sustain);
		};

	this->R_inner = compute_R_inner(burn_rate_func, dt);

	this->area = compute_area();
}

[[nodiscard]] double fuel::StarProfile::getBurnArea() const
{
	return this->area;
}


void fuel::StarProfile::updateTime(double dt)
{
	this->time += dt;
}

[[nodiscard]] double fuel::StarProfile::compute_area()
{
	double perimeter = compute_perimeter();
	
	if (currentMode == Mode::Boost) return L_boost * perimeter;
	else return L_sustain * perimeter;
}

[[nodiscard]] double fuel::StarProfile::compute_R_inner(BurnRateFunction burn_rate_func, double dt)
{
	//auto drdt = [this, &burn_rate_func](double t, double r_inner) {
	//	double old_R = this->R_inner;
	//
	//	this->R_inner = r_inner;
	//
	//	double temp_area = compute_area();
	//
	//	double br = burn_rate_func();
	//
	//	this->R_inner = old_R;
	//
	//	return br;
	//	}

	auto drdt = [&burn_rate_func](double t, double r_inner) {
		return burn_rate_func();
		};

	return rk4_step(drdt, R_inner, time, dt);
}


[[nodiscard]] double fuel::StarProfile::compute_perimeter() const {
	constexpr size_t N_points = 500;
	const double d_theta = 2.0 * M_PI / (N_points - 1);

	std::vector<double> x, y;
	x.reserve(N_points);
	y.reserve(N_points);

	for (size_t i = 0; i < N_points; ++i) {
		double t = i * d_theta;
		double r = compute_base_profile(t);
		double dr_dt = compute_derivity_base_profile(t);
		double integrand = std::sqrt(r * r + dr_dt * dr_dt);

		x.push_back(t);
		y.push_back(integrand);
	}

	return trapz(y, x);
}

[[nodiscard]] double fuel::StarProfile::compute_base_profile(double thetta) const
{
	return R_inner + Amp * cos(N * thetta);
}

[[nodiscard]] double fuel::StarProfile::compute_derivity_base_profile(double thetta) const
{
	return -Amp * N * sin(N * thetta);
}


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

[[nodiscard]] Mode fuel::StarProfile::getMode() const
{
	return this->currentMode
}