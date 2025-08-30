#pragma once
#include "IGuidanceHead.h"

namespace head
{
	template<typename IFace = IGuidanceHead>
	struct MyGuidanceHeadDynamicData final : public detail::IComponent::DynamicType {};

	template<typename IFace = IGuidanceHead>
	struct MyGuidanceHeadStaticData final : public detail::IComponent::StaticType {};

	class MyGuidanceHead final : public IGuidanceHead
	{
	public:
		explicit MyGuidanceHead();

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyGuidanceHeadDynamicData<> dyn_data;
		MyGuidanceHeadStaticData<> stat_data;
	};
}