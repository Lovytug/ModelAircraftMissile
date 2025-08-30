#pragma once
#include "../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace env_pres
{
	class IPressureModel : public detail::IComponent
	{
		virtual ~IPressureModel() = default;
	};
}