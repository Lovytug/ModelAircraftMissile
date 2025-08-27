#pragma once
#include "../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	class IFuelModelComputation : public detail::IComputeModule
	{
	public:
		virtual ~IFuelModelComputation() = default;
	};
}