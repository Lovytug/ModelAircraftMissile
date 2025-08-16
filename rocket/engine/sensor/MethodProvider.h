#pragma once
#include <memory>
#include "IDataProvider.h"

namespace sens
{
	template<class T>
	class MethodProvider : public IDataProvider
	{
	public:
		MethodProvider(std::shared_ptr<T> obj, double (T::*getter)() const) :
			obj(std::move(obj)), getter(getter) { }
			
		[[nodiscard]] double readValue() const override
		{
			return (obj.get()->*getter)();
		}

	private:
		std::shared_ptr<T> obj;
		double (T::*getter)() const;
	};
}

