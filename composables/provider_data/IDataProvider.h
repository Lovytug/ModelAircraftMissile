#pragma once
#include "../../util/IComponent/IComponent.h"
namespace sensor
{
	class IDataProvider : public IComponent
	{
	public:
		virtual ~IDataProvider() = default;
	};
}