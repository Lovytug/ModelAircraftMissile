#include "MyEnvironmentModelComputation.h"

env_comp::MyEnvironmentModelComputation::MyEnvironmentModelComputation(u_ptr<phis::IPhisicsModule> phisics, sh_ptr<detail::Time> time, std::string name)
	: phisics(std::move(phisics)), time(std::move(time))
{
	stat_data_cache.set<IEnvironmentModelComputation>("name", name);
	for (auto& [type, provider] : storage_) {
		stat_data_cache.subdataByIndex(type) = provider->getStaticData();
	}
}
void env_comp::MyEnvironmentModelComputation::updateState(const DynamicType& state)
{
	for (auto& [type, provider] : storage_) {
		try {
			provider->updateState(state.subdataByIndex(type));
		}
		catch (const std::runtime_error&) {

		}
	}
}

[[nodiscard]] const detail::IComputeModule::DynamicType& env_comp::MyEnvironmentModelComputation::getDynamicData() const noexcept
{
	dyn_data_cache = DynamicType();
	for (auto& [type, provider] : storage_) {
		dyn_data_cache.subdataByIndex(type) = provider->getDynamicData();
	}

	return dyn_data_cache;
}

[[nodiscard]] const detail::IComputeModule::StaticType& env_comp::MyEnvironmentModelComputation::getStaticData() const noexcept
{
	return stat_data_cache;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> env_comp::MyEnvironmentModelComputation::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}

[[nodiscard]] sh_ptr<detail::Time> env_comp::MyEnvironmentModelComputation::getTime() const noexcept
{
	return time;
}
