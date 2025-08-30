#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace head
{
	class IGuidanceHead : public detail::IComponent
	{
		virtual ~IGuidanceHead() = default;
	};
}