#pragma once
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include "../../util/IComponent/IComponent.h"
#include "../sensor/IDataProvider.h"
#include "../sensor/MethodProvider.h"

namespace comp
{
	class IComputeModule : IComponent
	{
	public:
		virtual ~IComputeModule() = default;

		template<typename T>
		virtual void setSesnor(u_ptr<sensor::IDataProvider>);

		template<typename T>
		virtual u_ptr<T> getSensor() const;

	protected:
		std::unordered_map<std::type_index, u_ptr<void>> storage_;
	};
}