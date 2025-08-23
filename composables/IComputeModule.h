#pragma once
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include "../util/IComponent/IComponent.h"
#include "provider_data/IDataProvider.h"
#include "provider_data/MethodProvider.h"

namespace comp
{
	class IComputeModule : IComponent
	{
	public:
		virtual ~IComputeModule() = default;

		template<typename T>
		virtual void setProvider(u_ptr<sensor::IDataProvider>);

		template<typename T>
		virtual u_ptr<T> getProvider() const;

	protected:
		std::unordered_map<std::type_index, u_ptr<void>> storage_;
	};
}