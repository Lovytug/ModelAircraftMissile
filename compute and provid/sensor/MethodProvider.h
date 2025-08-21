#pragma once
#include <memory>
#include <functional>
#include "../../util/global/global.h"
#include "IDataProvider.h"

namespace sensor
{
	template<class T>
	class MethodProvider : public IDataProvider
	{
	public:
		MethodProvider(sh_ptr<IComponent> component)
			: component_(std::dynamic_pointer_cast<T>(component))
		{
			if (!component_) {
				throw std::bad_cast();
			}
		}

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override
		{
			return component_->getDynamicData();
		}

		[[nodiscard]] StaticDataType& getStaticData() const noexcept override
		{
			return component_->getStaticData();
		}

		[[nodiscatd]] u_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept override
		{
			return component_->getPhisicFunc();
		}

		void updateState(const DynamicDataType&) override
		{
			component_->updateState(DynamicDataType);
		}
		
	private:
		sh_ptr<T> component_;
	};
}

