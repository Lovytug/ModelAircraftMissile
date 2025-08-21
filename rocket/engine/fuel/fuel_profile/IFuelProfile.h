#pragma once
#include "../../../../util/IComponent/IComponent.h"
#include "../switcher_regime/IModeObserver.h"
#include "../switcher_regime/IMethodObserver.h"

namespace fuel
{
	class IFuelProfile : public IComponent, public IMethodObserver
	{
	public:
		virtual ~IFuelProfile() = default;
	};
}