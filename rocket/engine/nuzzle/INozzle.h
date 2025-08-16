#pragma once
#include "../engine/IEngineComponent.h"
#include "../engine/IStateProvider.h"
#include "../sensor/IDataProvider.h"

namespace nuz
{
	class INuzzle : public IEngineComponent, public IStateProvider<INuzzle>
	{
		~INuzzle() = default;
		virtual [[nodiscard]] double getThrust() const = 0;
		virtual [[nodiscard]] double getMassFlowRate() const = 0;
	};
}