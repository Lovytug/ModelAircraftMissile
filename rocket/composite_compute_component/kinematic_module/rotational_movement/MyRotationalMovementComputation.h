#pragma once
#include "IRotationalMovementComputation.h"

namespace comp
{
	struct RotationalMovementComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct RotationalMovementComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyRotationalMovementComputation final : public IRotationalMovementComputation
	{
	public:
		explicit MyRotationalMovementComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable RotationalMovementComputationDynamicData dyn_data_cache;
		mutable RotationalMovementComputationStaticData stat_data_cache;
	};

}