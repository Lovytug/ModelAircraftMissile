#pragma once
#include "IFuelProfile.h"

namespace fuel
{
	class StarProfile : public IFuelProfile
	{
	public:
		explicit StarProfile(double R_0, double R_i_0, double L_boost, double L_sustain,
			double N, double amp, double thetta, std::string name);

		[[nodiscard]] double getBurnArea(const double burn_rate) const override;

	private:
		[[nodiscard]] double get_k_star() const;
		[[nodiscard]] double get_S_boost() const;
		[[nodiscard]] double get_S_sustain() const;
		[[nodiscard]] double base_profile() const;
		[[nodiscard]] double derivity_base_profile() const;

	private:
		double area;
		double R_i_0;

		const double R_o;
		const double L_boost;
		const double L_sustain;
		const double N;
		const double Amp;
		const double thetta;

		const std::string name;
	};
}