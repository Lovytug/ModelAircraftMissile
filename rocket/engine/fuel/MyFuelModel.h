#pragma once
#include <string>
#include "IFuelModel.h"
#include "fuel_profile/IFuelProfile.h"
#include "../global/global.h"

namespace fuel
{
	struct MyFuelDynamicData : DynamicDataType
	{
		MyFuelDynamicData(
			double burn_rate, double mass_flow_rate, Mode currentMode, 
			double area, double r_inner) {
			set("burn_rate", burn_rate);
			set("mass_flow_rate", mass_flow_rate);
			set("currentMode", currentMode);
			set("area", area);
			set("r_inner", r_inner)
		}
	};

	struct MyFuelStaticData : StaticDataType // надо расшир€ть дл€ остальных параметрв топлива
	{
		MyFuelStaticData(
			const double fuel_density, const float a_boost, const float a_sustain,
			const float n_boost, const float n_sustain, const std::string name
		) {
			set("fuel_density", fuel_density);
			set("a_boost", a_boost);
			set("a_sustain", a_sustain);
			set("n_boost", n_boost);
			set("n_sustain", n_sustain);
			set("name", name);
		}
	};

	class MyFuelModel : public IFuelModel
	{
	public:
		explicit MyFuelModel(
			IFuelProfile_uptr fuel_profile, IPhisicsModule_uptr phisics,
			double fuel_density, float a_boost, float a_sustain,
			float n_boost, float n_sustain, std::string name
		);

		void updateState(const MyFuelDynamicData&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscatd]] std::unique_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept override;

		void OnModeChanged(Mode newMode) override;

	private:
		IPhisicsModule_uptr phisics;
		IFuelProfile_uptr profile;
		MyFuelDynamicData dyn_data;
		MyFuelStaticData stat_data;
	};
}