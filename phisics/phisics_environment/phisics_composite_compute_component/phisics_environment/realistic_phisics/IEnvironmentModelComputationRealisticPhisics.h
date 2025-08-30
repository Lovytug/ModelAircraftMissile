#pragma once
#include "../../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class IEnvironmentModelComputationRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~IEnvironmentModelComputationRealisticPhisics() = default;
	};
}