#pragma once
#include "../IVectorStateDataType.h"

namespace mdt
{
	struct StaticDataType : public IVectorStateDataType {
		virtual ~StaticDataType() = default;
	};
}
