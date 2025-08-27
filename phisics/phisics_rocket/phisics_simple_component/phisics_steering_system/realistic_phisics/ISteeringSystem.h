#pragma once
#include "../../../../../base_component/provider_data/IDataProvider.h"
#include "../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class ISteeringSystem : public IRealisticPhisicsModule
	{
	public:
		virtual ~ISteeringSystem() = default;
	};
}