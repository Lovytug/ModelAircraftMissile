#pragma once
#include "../../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace steer
{
	class ISteeringSystem : public detail::IComponent
	{
		virtual ~ISteeringSystem() = default;
	};
}