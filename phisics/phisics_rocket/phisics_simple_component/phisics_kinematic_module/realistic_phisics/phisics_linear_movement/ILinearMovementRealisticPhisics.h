#pragma once
#include "../../../../../../base_component/provider_data/IDataProvider.h"
#include "../../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class ILinearMovementRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~ILinearMovementRealisticPhisics() = default;
	};
}