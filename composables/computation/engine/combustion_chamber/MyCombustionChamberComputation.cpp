#include "MyCombustionChamberComputation.h"

comp::MyCombustionChamberComputation::MyCombustionChamberComputation(u_ptr<phis::IPhisicsModule> phisics, std::string name)
	: phisics(std::move(phisics)), stat_data_cache(name)
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		stat_data_cache.set(name, provider->getStaticData());
	}
}
void comp::MyCombustionChamberComputation::updateState(const DynamicDataType& state)
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		sensor->updateState(state.get<DynamicDataType>(name));
	}
}

[[nodiscard]] DynamicDataType& comp::MyCombustionChamberComputation::getDynamicData() const noexcept
{
	for (auto& [type, provider] : storage_) {
		const auto& name = provider->getStaticData().get<std::string>("name");
		dyn_data_cache.set(name, provider->getDynamicData());
	}

	return dyn_data_cache;
}

[[nodiscard]] StaticDataType& comp::MyCombustionChamberComputation::getStaticData() const noexcept
{
	return stat_data_cache;
}

[[nodiscard]] u_ptr<phis::DynamicBundle> comp::MyCombustionChamberComputation::getPhisicFunc() const noexcept
{
	return phisics->getDynamicBundle();
}
