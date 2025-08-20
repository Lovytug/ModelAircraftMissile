#pragma once
#include <memory>

namespace phis
{
	struct DynamicBundle {
		virtual ~DynamicBundle() = default;
	};

	class IPhisicsModule
	{
	public:
		virtual ~IPhisicsModule() = default;
		virtual std::unique_ptr<DynamicBundle> getDynamicBundle() const = 0;
	};
}