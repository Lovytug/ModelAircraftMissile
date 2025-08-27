#pragma once
#include "INozzle.h"

namespace noz
{
	template<typename IFace = INozzle>
	struct MyNozzleDynamicData : public detail::IComponent::DynamicType
	{
		MyNozzleDynamicData(
			double mass_gaze_rate, double F_thrust,
			double V_effectiv, double temperature
		) {
			set<IFace>("mass_gaze_rate", mass_gaze_rate);
			set<IFace>("F_thrust", F_thrust);
			set<IFace>("V_effectiv", V_effectiv);
			set<IFace>("temperature", temperature);
		}
	};

	template<typename IFace = INozzle>
	struct MyNozzleStaticData : public detail::IComponent::StaticType
	{
		MyNozzleStaticData(
			const double critical_area_nozzle, const double adiabatic_index,
			const double R_g, const std::string name
		) {
			set<IFace>("critical_area_nozzle", critical_area_nozzle);
			set<IFace>("adiabatic_index", adiabatic_index);
			set<IFace>("R_g", R_g);
			set<IFace>("name", name);
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

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:   
		u_ptr<phis::IPhisicsModule> phisics;
		MyNozzleDynamicData<> dyn_data;
		MyNozzleStaticData<> stat_data;
	};
}