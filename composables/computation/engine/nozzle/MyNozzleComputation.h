#pragma once
#include "INozzleComputation.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	struct NozzleComputationDynamicData final : public DynamicDataType {};

	struct MyNozzleComputationStaticData final : public StaticDataType
	{
		MyNozzleComputationStaticData(const std::string name) {
			set("name", name);
		}
	};

	class MyNozzleComputation final : public INozzleComputation
	{
	public:
		explicit MyNozzleComputation(u_ptr<phis::IPhisicsModule>, std::string);

		void updateState(const DynamicDataType&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<DynamicBundle> getPhisicFunc() const noexcept override;

		template<typename T>
		void setProvider(u_ptr<sensor::IDataProvider>) override;

		template<typename T>
		u_ptr<T> getProvider() const override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		mutable NozzleComputationDynamicData dyn_data_cache; // ? Кэшируем данные
		mutable MyNozzleComputationStaticData stat_data_cache;
	};


	template<typename T>
	u_ptr<T> MyNozzleComputation::getProvider() const
	{
		auto it = storage_.find(std::type_index(typeid(T)));
		if (it == storage_.end()) {
			throw std::out_of_range("Type not found in map");
		}
		return std::static_pointer_cast<T>(it->second);
	}

	template<typename T>
	void MyNozzleComputation::setProvider(u_ptr<sensor::IDataProvider> value)
	{
		static_assert(!std::is_same_v<T, void>, "Cannot store void type");
		storage_[std::type_index(typeid(T))] = value;
	}
}