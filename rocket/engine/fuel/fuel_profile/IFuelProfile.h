#pragma once
#include "../../global/global.h"
#include "../switcher_regime/IModeObserver.h"
#include "../switcher_regime/IMethodObserver.h"

namespace fuel
{
	class IFuelProfile() : public IMethodObserver
	{
	public:
		~IFuelProfile() = default;
		virtual void update(BurnRateFunction burn_area, double dt) = 0;
		virtual [[nodiscard]] double getBurnArea() const = 0;
	}
}