#pragma once
#include <memory>
#include "../../../../util/IComponent/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace chamb
{
	class ICombustionChamber : public IComponent
	{
	public:
		virtual ~ICombustionChamber() = default;
	};
}