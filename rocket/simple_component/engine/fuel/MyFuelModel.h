#pragma once
#include <string>
#include "IFuelModel.h"

namespace fuel
{
	template<typename IFace = IFuelModel>
	struct MyFuelDynamicData final : detail::IComponent::DynamicType
	{
		MyFuelDynamicData(
			double burn_rate, double mass_flow_rate, Mode currentMode
		) {
			set<IFace>("burn_rate", burn_rate);
			set<IFace>("mass_flow_rate", mass_flow_rate);
			set<IFace>("currentMode", currentMode);
		}
	};

	template<typename IFace = IFuelModel>
	struct MyFuelStaticData final : detail::IComponent::StaticType
	{
		MyFuelStaticData(
			const double fuel_density, const float a_boost, const float a_sustain,
			const float n_boost, const float n_sustain, const std::string name
		) {
			set<IFace>("fuel_density", fuel_density);
			set<IFace>("a_boost", a_boost);
			set<IFace>("a_sustain", a_sustain);
			set<IFace>("n_boost", n_boost);
			set<IFace>("n_sustain", n_sustain);
			set<IFace>("name", name);
		}
	};

	class MyFuelModel final : public IFuelModel
	{
	public:
		explicit MyFuelModel(
			u_ptr<phis::IPhisicsModule> phisics,
			double fuel_density, float a_boost, float a_sustain,
			float n_boost, float n_sustain, std::string name
		);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyFuelDynamicData<> dyn_data;
		MyFuelStaticData<> stat_data;
	};
}