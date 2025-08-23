#pragma once
#include "../../../../util/IComponent/IComponent.h"
#include "../../../../phisics/IPhisicsModule.h"

namespace fuel
{
	class IFuelProfile : public IComponent
	{
	public:
		virtual ~IFuelProfile() = default;
	};
}