#pragma once
#include <string>
#include <vector>
#include <cmath>
#include "runge_kutta.h"
#include "trapz.h"
#include "IFuelProfile.h"

namespace fuel
{
	class StarProfile : public IFuelProfile
	{
	public:
		explicit StarProfile(double R_o, double R_i_0, double L_boost, double L_sustain,
			double N, double amp, double tetta, std::string name);

		void update(BurnRateFunction burn_rate_func, double dt) override;

		[[nodiscard]] double getBurnArea() const override;


		void notifyObservers() override;
		void registerObserver(IModeObserver& observer) override;
		void unregisterObserver(IModeObserver& observer) override;
		void setMode(Mode mode) override;
		[[nodiscard]] Mode getMode() const override;

	private:
		void updateTime(double dt);

		[[nodiscard]] double compute_area();
		[[nodiscard]] double compute_R_inner(BurnRateFunction burn_rate_func, double dt);
		[[nodiscard]] double compute_perimeter() const;
		[[nodiscard]] double compute_S_boost() const;
		[[nodiscard]] double compute_S_sustain() const;
		[[nodiscard]] double compute_base_profile(double theta) const;
		[[nodiscard]] double compute_derivity_base_profile(double theta) const;

	private:
		Mode currentMode;
		std::vector<IModeObserver&> observers;

		double area;
		double R_inner;
		double time;

		const double R_o;
		const double L_boost;
		const double L_sustain;
		const double N;
		const double Amp;
		const double theta;

		const std::string name;
	};
}