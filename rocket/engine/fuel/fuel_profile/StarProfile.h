#pragma once
#include <string>
#include <vector>
#include <cmath>
#include "runge_kutta.h"
#include "trapz.h"
#include "IFuelProfile.h"


namespace fuel
{
	struct StarProfileDynamicData : public DynamicDataType
	{
		StarProfileDynamicData(double area, double r_inner, Mode currentMode) {
			set("area", area);
			set("r_inner", r_inner);
			set("currentMode", currentMode);
		}
	};

	struct StarProfileStaticData : public StaticDataType
	{
		StarProfileStaticData(
			const double R_o, const double L_boost, const double L_sustain,
			const short N, const double Amp, const double theta, std::string name
		) {
			set("R_o", R_o);
			set("L_boost", L_boost);
			set("L_sustain", L_sustain);
			set("N", N);
			set("Amp", Amp);
			set("theta", theta);
			set("name", name);
		}
	};

	class StarProfile : public IFuelProfile
	{
	public:
		explicit StarProfile(IPhisicsModule_uptr phsics, double R_o, double R_i_0, double L_boost, double L_sustain,
			short N, double amp, double tetta, std::string name);

		void updateState(const DynamicDataType&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscatd]] std::unique_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept override;

		void notifyObservers() override;
		void registerObserver(IModeObserver& observer) override;
		void unregisterObserver(IModeObserver& observer) override;
		void setMode(Mode mode) override;
		[[nodiscard]] Mode getMode() const override;

	private:
		std::vector<std::unique_ptr<IModeObserver>> observers;
		IPhisicsModule_uptr phisics;
		StarProfileDynamicData dyn_data;
		StarProfileStaticData stat_data;
	};
}