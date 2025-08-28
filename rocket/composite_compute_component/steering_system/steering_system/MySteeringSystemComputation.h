#pragma once
#include "ISteeringSystemComputation.h"

namespace comp
{
	struct SteeringSystemComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct SteeringSystemComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MySteeringSystemComputation final : public ISteeringSystemComputation
	{
	public:
		explicit MySteeringSystemComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable SteeringSystemComputationDynamicData dyn_data_cache;
		mutable SteeringSystemComputationStaticData stat_data_cache;
	};
}