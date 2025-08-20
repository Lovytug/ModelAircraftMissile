#include "StarProfileRealisticPhisics.h"

[[nodiscard]] double phis::StarProfileRealisticPhisics::compute_area(const fuel::IFuelProfile& profile)
{
	auto state = profile.getStaticData();
	if (profile.getDynamicData().get<fuel::Mode>("currentMode") == Mode::Boost) 
		return state.get<double>("L_boost") * compute_perimeter();
	else 
		return state.get<double>("L_sustain") * compute_perimeter();
}

[[nodiscard]] double phis::StarProfileRealisticPhisics::compute_dr_inner(const fuel::IFuelProfile& profile, const double burn_rate)
{
	return burn_rate;
}

[[nodiscard]] double phis::StarProfileRealisticPhisics::compute_perimeter(const fuel::IFuelProfile& profile) const
{
	constexpr size_t N_points = 500;
	const double d_theta = 2.0 * M_PI / (N_points - 1);

	std::vector<double> x, y;
	x.reserve(N_points);
	y.reserve(N_points);

	for (size_t i = 0; i < N_points; ++i) {
		double t = i * d_theta;
		double r = compute_base_profile(profile, t);
		double dr_dt = compute_derivity_base_profile(profile, t);
		double integrand = std::sqrt(r * r + dr_dt * dr_dt);

		x.push_back(t);
		y.push_back(integrand);
	}

	return trapz(y, x);
}

[[nodiscard]] double phis::StarProfileRealisticPhisics::compute_base_profile(const fuel::IFuelProfile& profile, double theta) const
{
	auto state = profile.getStaticData();
	return profile.getDynamicData().get<double>("r_inner") + state.get<double>("Amp") * cos(state.get<short>("N") * theta);
}

[[nodiscard]] double phis::StarProfileRealisticPhisics::compute_derivity_base_profile(const fuel::IFuelProfile& profile, double theta) const
{
	auto state = profile.getStaticData();
	return -state.get<double>("Amp") * N * sin(state.get<short>("N") * thetta);
}

[[nodiscard]] std::unique_ptr<DynamicBundle> phis::StarProfileRealisticPhisics::getDynamicBundle() const
{
	bundle = std::make_unique<FuelModelDynamicBundle>();

	bundle->area_func = [this](const auto& fuel) {
		return compute_area(fuel);
		};

	bundle->dr_inner_func = [this](const auto& fuel, double burn_rate) {
		return compute_dr_inner(fuel, burn_rate);
		};

	return bundle;
}