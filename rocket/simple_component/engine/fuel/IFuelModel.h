#pragma once
#include "mode_regime/ModeRegime.h"
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace fuel
{
	class IFuelModel : public detail::IComponent
	{
	public:
		virtual ~IFuelModel() = default;
	};
}