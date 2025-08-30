#include "MyGuidanceHeadComputation.h"

comp::MyGuidanceHeadComputation::MyGuidanceHeadComputation(u_ptr<phis::IPhisicsModule> phisics, sh_ptr<detail::Time> time, std::string name)
	: phisics(std::move(phisics)), time(std::move(time))
{
	stat_data_cache.set<IGuidanceHeadComputation>("name", name);
	for (auto& [type, provider] : storage_) {
		stat_data_cache.subdataByIndex(type) = provider->getStaticData();
	}
}

void comp::MyGuidanceHeadComputation::updateState(const DynamicType& state)
{
	for (auto& [type, provider] : storage_) {
		try {
			provider->updateState(state.subdataByIndex(type));
		}
		catch (const std::runtime_error&) {

		}
	}
}

[[nodiscard]] const detail::IComputeModule::DynamicType& comp::MyGuidanceHeadComputation::getDynamicData() const noexcept
{
	dyn_data_cache = DynamicType();
	for (auto& [type, provider] : storage_) {
		dyn_data_cache.subdataByIndex(type) = provider->getDynamicData();
	}

	return dyn_data_cache;
}

[[nodiscard]] const detail::IComputeModule::StaticType& comp::MyGuidanceHeadComputation::getStaticData() const noexcept
{
	return stat_data_cache;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> comp::MyGuidanceHeadComputation::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}

[[nodiscard]] sh_ptr<detail::Time> comp::MyGuidanceHeadComputation::getTime() const noexcept
{
	return time;
}