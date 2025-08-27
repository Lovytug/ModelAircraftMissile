#pragma once
#include "IEngineComputation.h"

namespace comp
{
	struct EngineComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct EngineComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyEngineComputation final : public IEngineComputation
	{
	public:
		explicit MyEngineComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable EngineComputationDynamicData dyn_data_cache;
		mutable EngineComputationStaticData stat_data_cache;
	};
}