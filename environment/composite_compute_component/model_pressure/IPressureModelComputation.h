#pragma once
#include "../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../phisics/IPhisicsModule.h"

namespace env_comp
{
	class IPressureModelComputation : public detail::IComputeModule
	{
	public:
		virtual ~IPressureModelComputation() = default;
	};
}