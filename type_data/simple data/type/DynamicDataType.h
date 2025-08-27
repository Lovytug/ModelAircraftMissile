#pragma once
#include "../IVectorStateDataType.h"
#include "TypeData.h"

namespace mdt
{
	struct DynamicDataType : public IVectorStateDataType {
		virtual ~DynamicDataType() = default;

	protected:
		std::shared_ptr<IVectorStateDataType> createSubdata() const override {
			return std::make_shared<DynamicDataType>();
		}
	};
}