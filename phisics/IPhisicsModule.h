#pragma once
#include "../base_component/global/global.h"
#include "../type_data/bundle/DynamicBundle.h"
#include <memory>

namespace phis
{
	class IPhisicsModule
	{
	public:
		virtual ~IPhisicsModule() = default;
		virtual [[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const = 0;
	};
}