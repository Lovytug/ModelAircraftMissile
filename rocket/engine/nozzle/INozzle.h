#pragma once
#include <memory>
#include "../../../../util/IComponent/IComponent.h"
#include "../../../phisics/IPhisicsModule.h"

namespace noz
{
	class INozzle : public IComponent
	{
		virtual ~INozzle() = default;
	};
}