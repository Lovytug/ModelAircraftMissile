#pragma once
#include "switcher_regime/IModeObserver.h"
#include "../../../util/TypeData/DynamicDataType.h"
#include "../../../util/TypeData/StaticDataType.h"
#include "../../../util/global/global.h"
#include "../../../phisics/IPhisicsModule.h"

namespace fuel
{
	class IFuelModel : public IModeObserver
	{
	public:
		virtual ~IFuelModel() = default;
		virtual [[nodiscard]] DynamicDataType& getDynamicData() const noexcept = 0;
		virtual [[nodiscard]] StaticDataType& getStaticData() const noexcept = 0;
		virtual [[nodiscatd]] u_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept = 0;
		virtual void updateState(const DynamicDataType&) = 0;
	};
}