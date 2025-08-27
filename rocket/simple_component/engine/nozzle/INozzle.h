#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace noz
{
	class INozzle : public detail::IComponent
	{
		virtual ~INozzle() = default;
	};
}