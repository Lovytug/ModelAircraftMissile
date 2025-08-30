#pragma once
#include "../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../phisics/IPhisicsModule.h"

namespace env_comp
{
	class IDensityModelComputation : public detail::IComputeModule
	{
	public:
		virtual ~IDensityModelComputation() = default;
	};
}