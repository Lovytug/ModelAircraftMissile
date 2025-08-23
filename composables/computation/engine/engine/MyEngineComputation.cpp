#include "MyEngineComputation.h"

comp::MyEngineComputation::MyEngineComputation(u_ptr<phis::IPhisicsModule> phisics, std::string name)
	: phisics(std::move(phisics)), stat_data_cache(name)
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		stat_data_cache.set(name, provider->getStaticData());
	}
}
void comp::MyEngineComputation::updateState(const DynamicDataType& state)
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		sensor->updateState(state.get<DynamicDataType>(name));
	}
}

[[nodiscard]] DynamicDataType& comp::MyEngineComputation::getDynamicData() const noexcept
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		dyn_data_cache.set(name, provider->getDynamicData());
	}

	return dyn_data_cache;
}

[[nodiscard]] StaticDataType& comp::MyEngineComputation::getStaticData() const noexcept
{
	return stat_data_cache;
}

[[nodiscard]] u_ptr<phis::DynamicBundle> comp::MyEngineComputation::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle();
}
