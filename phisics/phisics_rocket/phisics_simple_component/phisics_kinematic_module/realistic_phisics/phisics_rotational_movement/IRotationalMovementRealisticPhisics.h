#pragma once
#include "../../../../../../base_component/provider_data/IDataProvider.h"
#include "../../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class IRotationalMovementRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~IRotationalMovementRealisticPhisics() = default;
	};
}