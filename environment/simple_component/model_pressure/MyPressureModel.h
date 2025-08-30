#pragma once
#include "IPressureModel.h"

namespace env_pres
{
	template<typename IFace = IPressureModel>
	struct MyPressureDynamicData : public detail::IComponent::DynamicType {};

	template<typename IFace = IPressureModel>
	struct MyPressureStaticData : public detail::IComponent::StaticType {};

	class MyPressureModel final : public IPressureModel
	{
	public:
		explicit MyPressureModel(u_ptr<phis::IPhisicsModule>);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyPressureDynamicData<> dyn_data;
		MyPressureStaticData<> stat_data;
	};
}