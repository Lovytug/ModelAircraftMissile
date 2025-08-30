#pragma once
#include "../../../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class ILinearMovementComputationRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~ILinearMovementComputationRealisticPhisics() = default;
	};
}