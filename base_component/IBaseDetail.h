#pragma once
#include "global/global.h"
#include "../type_data/bundle/DynamicBundle.h"
#include "../type_data/simple data/VectorDataType.h"

namespace detail
{
	class IBaseDetail
	{
		using DynamicType = mdt::VectorDataType;
		using StaticType = mdt::VectorDataType;
		
		virtual ~IBaseDetail() = default;

		virtual [[nodiscard]] const DynamicType& getDynamicData() const noexcept = 0;
		virtual [[nodiscard]] const StaticType& getStaticData() const noexcept = 0;
		virtual [[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept = 0;
		virtual void updateState(const DynamicType&) = 0;
	};
}