#pragma once
#include "../engine/IEngineComponent.h"
#include "../engine/IStateProvider.h"
#include "../sensor/IDataProvider.h"
#include "switcher_regime/IModeObserver.h"

namespace fuel
{
	class IFuelModel : 
		public IEngineComponent, 
		public IStateProvider<IFuelModel>, 
		public IModeObserver
	{
	public:
		virtual [[nodiscard]] double getMassFlowRate() const = 0;
	};
}