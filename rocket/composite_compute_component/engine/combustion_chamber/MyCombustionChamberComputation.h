#pragma once
#include "ICombustionChamberComputation.h"

namespace comp
{
	struct CombustionChamberDynamicData final : public detail::IComputeModule::DynamicType {};

	struct CombustionChamberStaticData final : public detail::IComputeModule::StaticType {};

	class MyCombustionChamberComputation final : public ICombustionChamberComputation
	{
	public:
		explicit MyCombustionChamberComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string name);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable CombustionChamberDynamicData dyn_data_cache;
		mutable CombustionChamberStaticData stat_data_cache;
	};
}