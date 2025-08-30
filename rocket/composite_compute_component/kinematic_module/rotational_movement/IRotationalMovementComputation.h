#pragma once
#include "../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	class IRotationalMovementComputation : public detail::IComputeModule
	{
	public:
		virtual ~IRotationalMovementComputation() = default;
	};
}