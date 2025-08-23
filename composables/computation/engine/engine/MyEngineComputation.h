#pragma once
#include <iostream>
#include "IEngineComputation.h"
#include "../../../../rocket/engine/fuel/IFuelModel.h"
#include "../../../../rocket/engine/nozzle/INozzle.h"
#include "../../../../rocket/engine/combustion_chamber/ICombustionChamber.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	struct EngineComputationDynamicData final : public DynamicDataType {};

	struct EngineComputationStaticData final : public StaticDataType
	{
		EngineComputationStaticData(const std::string name) {
			set("name", name);
		}
	};

	class MyEngineComputation final : public IEngineComputation
	{
	public:
		explicit MyEngineComputation(u_ptr<phis::IPhisicsModule>, std::string);

		void updateState(const DynamicDataType&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept override;

		template<typename T>
		void setProvider(u_ptr<sensor::IDataProvider>) override;

		template<typename T>
		u_ptr<T> getProvider() const override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		mutable EngineComputationDynamicData dyn_data_cache;
		mutable EngineComputationStaticData stat_data_cache;
	};


	template<typename T>
	u_ptr<T> MyEngineComputation::getProvider() const
	{
		auto it = storage_.find(std::type_index(typeid(T)));
		if (it == storage_.end()) {
			throw std::out_of_range("Type not found in map");
		}
		return std::static_pointer_cast<T>(it->second);
	}

	template<typename T>
	void MyEngineComputation::setProvider(u_ptr<sensor::IDataProvider> value)
	{
		static_assert(!std::is_same_v<T, void>, "Cannot store void type");
		storage_[std::type_index(typeid(T))] = value;
	}
}