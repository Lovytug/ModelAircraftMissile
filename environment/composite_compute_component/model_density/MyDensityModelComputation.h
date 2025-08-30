#pragma once
#include "IDensityModelComputation.h"

namespace env_comp
{
	struct DensityModelComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct DensityModelComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyDensityModelComputation final : public IDensityModelComputation
	{
	public:
		explicit MyDensityModelComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable DensityModelComputationDynamicData dyn_data_cache;
		mutable DensityModelComputationStaticData stat_data_cache;
	};

}