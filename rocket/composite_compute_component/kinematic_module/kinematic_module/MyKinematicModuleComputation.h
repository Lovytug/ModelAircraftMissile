#pragma once
#include "IKinematicModuleComputation.h"

namespace comp
{
	struct KinematicModuleComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct KinematicModuleComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyKinematicModuleComputation final : public IKinematicModuleComputation
	{
	public:
		explicit MyKinematicModuleComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable KinematicModuleComputationDynamicData dyn_data_cache;
		mutable KinematicModuleComputationStaticData stat_data_cache;
	};

}