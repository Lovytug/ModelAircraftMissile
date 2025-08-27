#pragma once
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include "../time/Time.h"
#include "../IBaseDetail.h"
#include "../provider_data/IDataProvider.h"
#include "../provider_data/MethodProvider.h"

namespace detail
{
	class IComputeModule : public IBaseDetail
	{
	public:
		virtual ~IComputeModule() = default;

		virtual [[nodiscard]] sh_ptr<Time> getTime() const noexcept = 0;

		template<typename T>
		void setProvider(u_ptr<T> provider)
		{
			static_assert(std::is_base_of_v<IDataProvider, T>,
				"T must derive from IDataProvider");

			storage_[std::type_index(typeid(T))] = provider;
		}

		template<typename T>
		u_ptr<T> getProvider() const
		{
			static_assert(std::is_base_of_v<detail::IDataProvider, T>,
				"T must derive from IDataProvider");

			auto it = storage_.find(std::type_index(typeid(T)));
			if (it == storage_.end()) {
				throw std::out_of_range("Type not found in map");
			}
			return std::static_pointer_cast<T>(it->second);
		}

	protected:
		std::unordered_map<std::type_index, u_ptr<IDataProvider>> storage_;
	};
}