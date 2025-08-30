#pragma once
#include "IDensityModel.h"

namespace env_dens
{
	template<typename IFace = IDensityModel>
	struct MyDensityDynamicData : public detail::IComponent::DynamicType {};

	template<typename IFace = IDensityModel>
	struct MyDensityStaticData : public detail::IComponent::StaticType {};

	class MyDensityModel final : public IDensityModel
	{
	public:
		explicit MyDensityModel(u_ptr<phis::IPhisicsModule>);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyDensityDynamicData<> dyn_data;
		MyDensityStaticData<> stat_data;
	};
}