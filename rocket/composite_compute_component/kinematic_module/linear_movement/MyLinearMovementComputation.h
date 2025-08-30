#pragma once
#include "ILinearMovementComputation.h"

namespace comp
{
	struct LinearMovementComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct LinearMovementComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyLinearMovementComputation final : public ILinearMovementComputation
	{
	public:
		explicit MyLinearMovementComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable LinearMovementComputationDynamicData dyn_data_cache;
		mutable LinearMovementComputationStaticData stat_data_cache;
	};

}