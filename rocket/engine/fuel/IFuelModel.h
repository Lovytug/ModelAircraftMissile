#pragma once
#include "../engine/IEngineComponent.h"
#include "../engine/IStateProvider.h"
#include "../sensor/IDataProvider.h"

namespace fuel
{
	class IFuelModel : public IEngineComponent, public IStateProvider<IFuelModel>
	{
	public:
		virtual [[nodiscard]] double getMassFlowRate() const = 0;
	};
}