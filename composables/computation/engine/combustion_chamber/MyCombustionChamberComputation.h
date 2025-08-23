#pragma once
#include "ICombustionChamberComputation.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	struct CombustionChamberDynamicData final : public DynamicDataType {};

	struct CombustionChamberStaticData final : public StaticDataType
	{
		CombustionChamberStaticData(const std::string name) {
			set("name", name);
		}
	};

	class MyCombustionChamberComputation final : public ICombustionChamberComputation
	{
	public:
		explicit MyCombustionChamberComputation(u_ptr<phis::IPhisicsModule>, std::string name);

		void updateState(const DynamicDataType&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept override;

		void setProvider(u_ptr<sensor::IDataProvider>) override;

		template<typename T>
		u_ptr<T> getProvider() const override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		mutable CombustionChamberDynamicData dyn_data_cache; // ? Кэшируем данные
		mutable CombustionChamberStaticData stat_data_cache;
	};


	template<typename T>
	u_ptr<T> MyCombustionChamberComputation::getProvider() const
	{
		auto it = storage_.find(std::type_index(typeid(T)));
		if (it == storage_.end()) {
			throw std::out_of_range("Type not found in map");
		}
		return std::static_pointer_cast<T>(it->second);
	}

	template<typename T>
	void MyCombustionChamberComputation::setProvider(u_ptr<sensor::IDataProvider> value)
	{
		static_assert(!std::is_same_v<T, void>, "Cannot store void type");
		storage_[std::type_index(typeid(T))] = value;
	}
}