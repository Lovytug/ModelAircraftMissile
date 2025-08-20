#pragma once
#include <memory>
#include <functional>
#include "IDataProvider.h"

namespace sensor
{
	template<class T>
	class MethodProvider : public IDataProvider
	{
	public:
		MethodProvider(std::shared_ptr<T> obj, std::function<double(const T&, double)> f) 
			: obj(std::move(obj)),
			func([this, f](double param) {return f(*this->obj, param); }) {}
			
		[[nodiscard]] double read(double param) const override
		{
			return func(param);
		}

	private:
		std::shared_ptr<T> obj;
		std::function<double(double)> func;
	};
}

