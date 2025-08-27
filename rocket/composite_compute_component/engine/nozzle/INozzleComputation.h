#pragma once
#include "../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace comp
{
	class INozzleComputation : public detail::IComputeModule
	{
	public:
		virtual ~INozzleComputation() = default;
	};
}