#pragma once
#include "../../../util/IComponent/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace fuel
{
	class IFuelModel : public IComponent
	{
	public:
		virtual ~IFuelModel() = default;
	};
}