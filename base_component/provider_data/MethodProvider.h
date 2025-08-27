#pragma once
#include <memory>
#include <functional>
#include "../global/global.h"
#include "IDataProvider.h"

namespace detail
{
	template<class IFace>
	class MethodProvider final : public IDataProvider
	{
	public:
		explicit MethodProvider(sh_ptr<IFace> component)
			: component_(std::dynamic_pointer_cast<IFace>(component))
		{
			static_assert(
				requires(IFace f) {
					{ f.getDynamicData() } -> std::same_as<DynamicType&>;
					{ f.getStaticData() } -> std::same_as<StaticType&>;
				},
				"IFace must have getDynamicData()/getStaticData methods returning DynamicType&/StaticType&"
			);

			if (!component_) {
				throw std::invalid_argument(
					std::string("MethodProvider<") +
					typeid(IFace).name() +
					">: component does not implement the required interface"
				);
			}
		}

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override
		{
			return static_cast<const DynamicType&>(component_->getDynamicData());
		}

		[[nodiscard]] const StaticType& getStaticData() const noexcept override
		{
			return static_cast<const StaticType&>(component_->getStaticData());
		}

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override
		{
			return static_cast<u_ptr<mdt::DynamicBundle>>(component_->getPhisicsFunc());
		}

		void updateState(const DynamicType& data) override
		{
			component_->updateState(data);
		}

		const std::type_info& interfaceType() const noexcept override
		{
			return typeid(IFace);
		}
		
	private:
		sh_ptr<IFace> component_;
	};
}

