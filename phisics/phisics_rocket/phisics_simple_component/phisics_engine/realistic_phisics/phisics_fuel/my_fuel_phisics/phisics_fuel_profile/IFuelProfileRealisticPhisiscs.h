#pragma once
#include "../../../../../../../../base_component/provider_data/IDataProvider.h"
#include "../../../../../../../type phisics/realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class IFuelProfileRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		virtual ~IFuelProfileRealisticPhisics() = default;
	};
}