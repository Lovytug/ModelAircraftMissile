#pragma once
#include "IPressureModelComputation.h"

namespace env_comp
{
	struct PressureModelComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct PressureModelComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyPressureModelComputation final : public IPressureModelComputation
	{
	public:
		explicit MyPressureModelComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable PressureModelComputationDynamicData dyn_data_cache;
		mutable PressureModelComputationStaticData stat_data_cache;
	};

}