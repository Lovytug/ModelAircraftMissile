#pragma once
#include "IEnvironmentModelComputation.h"

namespace env_comp
{
	struct EnvironmentModelComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct EnvironmentModelComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyEnvironmentModelComputation final : public IEnvironmentModelComputation
	{
	public:
		explicit MyEnvironmentModelComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable EnvironmentModelComputationDynamicData dyn_data_cache;
		mutable EnvironmentModelComputationStaticData stat_data_cache;
	};

}