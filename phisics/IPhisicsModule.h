#pragma once
#include "../util/TypeData/DynamicBundle.h"
#include <memory>

namespace phis
{
	class IPhisicsModule
	{
	public:
		virtual ~IPhisicsModule() = default;
		virtual [[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const = 0;
	};
}