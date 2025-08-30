#pragma once
#include "IGuidanceHeadComputation.h"

namespace comp
{
	struct GuidanceHeadComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct GuidanceHeadComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyGuidanceHeadComputation final : public IGuidanceHeadComputation
	{
	public:
		explicit MyGuidanceHeadComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable GuidanceHeadComputationDynamicData dyn_data_cache;
		mutable GuidanceHeadComputationStaticData stat_data_cache;
	};
}