#pragma once
#include "INozzleComputation.h"

namespace comp
{
	struct NozzleComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct MyNozzleComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyNozzleComputation final : public INozzleComputation
	{
	public:
		explicit MyNozzleComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable NozzleComputationDynamicData dyn_data_cache;
		mutable MyNozzleComputationStaticData stat_data_cache;
	};

}