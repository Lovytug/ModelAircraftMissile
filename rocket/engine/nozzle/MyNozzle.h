#pragma once
#include "INozzle.h"

namespace noz
{
	struct MyNozzleDynamicData : public DynamicDataType
	{
		MyNozzleDynamicData(
			double mass_gaze_rate, double F_thrust,
			double V_effectiv, double temperature
		) {
			set("mass_gaze_rate", mass_gaze_rate);
			set("F_thrust", F_thrust);
			set("V_effectiv", V_effectiv);
			set("temperature", temperature);
		}
	};

	struct MyNozzleStaticData : public StaticDataType
	{
		MyNozzleStaticData(
			const double critical_area_nozzle, const double adiabatic_index,
			const double R_g, const std::string name
		) {
			set("critical_area_nozzle", critical_area_nozzle);
			set("adiabatic_index", adiabatic_index);
			set("R_g", R_g);
			set("name", name);
		}
	};

	class MyNozzle : public INozzle
	{
	public:
		explicit MyNozzle(
			u_ptr<phis::IPhisicsModule> phisics,
			double critical_area_nozzle, double adiabatic_index,
			double V_effectiv, double temperature, 
			double R_g, std::string name
		);

		void updateState(const MyNozzleDynamicData&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscatd]] u_ptr<DynamicBundle> getPhisicFunc() const noexcept override;


	private:   
		u_ptr<phis::IPhisicsModule> phisics;
		MyNozzleDynamicData dyn_data;
		MyNozzleStaticData stat_data;
	};
}