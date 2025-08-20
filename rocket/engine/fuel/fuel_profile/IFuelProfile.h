#pragma once
#include "../../global/global.h"
#include "../../../util/TypeData/DynamicDataType.h"
#include "../../../util/TypeData/StaticDataType.h"
#include "../switcher_regime/IModeObserver.h"
#include "../switcher_regime/IMethodObserver.h"

namespace fuel
{
	class IFuelProfile : public IMethodObserver
	{
	public:
		virtual ~IFuelProfile() = default;
		virtual [[nodiscard]] DynamicDataType& getDynamicData() const noexcept = 0;
		virtual [[nodiscard]] StaticDataType& getStaticData() const noexcept = 0;
		virtual [[nodiscatd]] std::unique_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept = 0;
		virtual void updateState(const DynamicDataType&) = 0;
	};
}