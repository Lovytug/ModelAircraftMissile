#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace kin_rot
{
	class IRotationalMovement : public detail::IComponent
	{
		virtual ~IRotationalMovement() = default;
	};
}