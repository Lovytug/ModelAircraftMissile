#pragma once
#include "../engine/IEngineComponent.h"
#include "../engine/IStateProvider.h"
#include "../sensor/IDataProvider.h"

namespace chamb
{
	class ICombustionChamber : public IEngineComponent, public, IStateProvader<ICombustionChamber>
	{
	public:
		~ICombustionChamber() = default;
		virtual [[nodiscard]] double getPressure() const = 0;
		virtual [[nodiscard]] double getTemperature() const = 0;
	};
}