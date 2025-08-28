#pragma once
#include "../../../../../../base_component/rocket_composite_component/IComputeModule.h"
#include "../../../../../type phisics/realistic/IRealisticPhisicsModule.h

namespace phis
{
	class ISteeringSystemComputationRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~ISteeringSystemComputationRealisticPhisics() = default;
	};
}