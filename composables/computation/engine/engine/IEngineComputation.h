#pragma once
#include "../../../IComputeModule.h"

namespace comp
{
	class IEngineComputation : public IComputeModule
	{
	public:
		virtual ~IEngineComputation() = default
	};
}