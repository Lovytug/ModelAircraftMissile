#pragma once
#include "../IBaseDetail.h"

namespace detail
{
	class IComponent : public IBaseDetail
	{
	public:
		virtual ~IComponent() = default;
	};
}