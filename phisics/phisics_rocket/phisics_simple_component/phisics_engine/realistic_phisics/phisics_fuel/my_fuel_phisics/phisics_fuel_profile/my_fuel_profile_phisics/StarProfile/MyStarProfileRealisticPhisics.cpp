#include <vector>
#include <cmath>
#include "trapz.h"
#include "MyStarProfileRealisticPhisics.h"

phis::MyStarProfileRealisticPhisics::MyStarProfileRealisticPhisics() {}

[[nodiscard]] double phis::MyStarProfileRealisticPhisics::compute_area(const detail::IDataProvider& profile)
{
	auto state = profile.getStaticData();
	if (profile.getDynamicData().get<fuel::Mode>("currentMode") == fuel::Mode::Boost) 
		return state.get<double>("L_boost") * compute_perimeter();
	else 
		return state.get<double>("L_sustain") * compute_perimeter();
}

[[nodiscard]] double phis::MyStarProfileRealisticPhisics::compute_dr_inner(const detail::IDataProvider& profile, const double burn_rate)
{
	return burn_rate;
}

[[nodiscard]] double phis::MyStarProfileRealisticPhisics::compute_perimeter(const detail::IDataProvider& profile) const
{
	constexpr size_t N_points = 300;
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

[[nodiscard]] double phis::MyStarProfileRealisticPhisics::compute_base_profile(const detail::IDataProvider& profile, double theta) const
{
	auto state = profile.getStaticData();
	return profile.getDynamicData().get<double>("r_inner") + state.get<double>("Amp") * cos(state.get<short>("N") * theta);
}

[[nodiscard]] double phis::MyStarProfileRealisticPhisics::compute_derivity_base_profile(const detail::IDataProvider& profile, double theta) const
{
	auto state = profile.getStaticData();
	return -state.get<double>("Amp") * state.get<short>("N") * sin(state.get<short>("N") * theta);
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyStarProfileRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<FuelProfileDynamicBundle>();

	bundle->add<double, const detail::IDataProvider&>(
		"area_func",
		[this](const detail::IDataProvider& profile) -> double {
			return compute_area(profile);
		}
	);

	bundle->add<double, const detail::IDataProvider&, double>(
		"dr_inner_func",
		[this](const detail::IDataProvider& profile, double burn_rate) -> double {
			return compute_dr_inner(profile, burn_rate);
		}
	);

	return bundle;
}