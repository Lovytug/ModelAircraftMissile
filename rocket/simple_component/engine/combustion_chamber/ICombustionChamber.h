#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace chamb
{
	class ICombustionChamber : public detail::IComponent
	{
	public:
		virtual ~ICombustionChamber() = default;
	};
}