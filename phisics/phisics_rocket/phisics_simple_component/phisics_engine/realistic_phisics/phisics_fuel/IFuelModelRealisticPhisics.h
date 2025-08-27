#pragma once
#include "../../../../../../base_component/provider_data/IDataProvider.h"
#include "../../../../../type phisics/realistic/IRealisticPhisicsModule.h

namespace phis
{
	class IFuelModelRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~IFuelModelRealisticPhisics() = default;
	};
}