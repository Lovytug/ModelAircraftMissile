#pragma once
#include "../../../base_component/rocket_simple_component/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace env_dens
{
	class IDensityModel : public detail::IComponent
	{
		virtual ~IDensityModel() = default;
	};
}