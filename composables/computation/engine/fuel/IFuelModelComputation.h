#pragma once
#include "../../../IComputeModule.h"

namespace comp
{
	class IFuelModelComputation : public IComponent
	{
	public:
		virtual ~IFuelModelComputation() = default;
	};
}