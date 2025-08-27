#pragma once
#include "../IBaseDetail.h"

namespace detail
{
	class IDataProvider : public IBaseDetail
	{
	public:
		virtual ~IDataProvider() = default;

		virtual const std::type_info& interfaceType() const noexcept = 0;
	};
}