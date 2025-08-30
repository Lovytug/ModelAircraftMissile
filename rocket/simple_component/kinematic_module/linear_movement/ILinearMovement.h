#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace kin_lin
{
	class ILinearMovement : public detail::IComponent
	{
		virtual ~ILinearMovement() = default;
	};
}