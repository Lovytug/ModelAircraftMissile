#pragma once
#include "../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../phisics/IPhisicsModule.h"

namespace env_comp
{
	class IEnvironmentModelComputation : public detail::IComputeModule
	{
	public:
		virtual ~IEnvironmentModelComputation() = default;
	};
}