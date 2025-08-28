#pragma once
#include "IFuelModelComputation.h"

namespace comp
{
	struct FuelModelComputationDynamicData final : public detail::IComputeModule::DynamicType {};

	struct FuelModelComputationStaticData final : public detail::IComputeModule::StaticType {};

	class MyFuelModelComputation final : public IFuelModelComputation
	{
	public:
		explicit MyFuelModelComputation(u_ptr<phis::IPhisicsModule>, sh_ptr<detail::Time>, std::string);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;
		[[nodiscard]] sh_ptr<detail::Time> getTime() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		sh_ptr<detail::Time> time;
		mutable FuelModelComputationDynamicData dyn_data_cache;
		mutable FuelModelComputationStaticData stat_data_cache;
	};
}