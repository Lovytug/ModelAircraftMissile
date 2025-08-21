#pragma once
#include "switcher_regime/IModeObserver.h"
#include "../../../util/IComponent/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace fuel
{
	class IFuelModel : public IComponent, public IModeObserver
	{
	public:
		virtual ~IFuelModel() = default;
	};
}