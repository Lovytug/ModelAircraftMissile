#pragma once
#include "../TypeData/bundle/DynamicBundle.h"
#include "../TypeData/DynamicDataType.h"
#include "../TypeData/StaticDataType.h"
#include "../global/global.h"

class IComponent
{
public:
	virtual ~IComponent() = default;
	virtual [[nodiscard]] DynamicDataType& getDynamicData() const noexcept = 0;
	virtual [[nodiscard]] StaticDataType& getStaticData() const noexcept = 0;
	virtual [[nodiscatd]] u_ptr<phis::DynamicBundle> getPhisicFunc() const noexcept = 0;
	virtual void updateState(const DynamicDataType&) = 0;
};