#pragma once
#include "IModeObserver.h"

namespace fuel
{
	class IMethodObserver
	{
	public:
		virtual ~IMethodObserver() = default;
		virtual void notifyObservers() = 0;
		virtual void registerObserver(IModeObserver& observer) = 0;
		virtual void unregisterObserver(IModeObserver& observer) = 0;
		virtual void setMode(Mode mode);
		virtual [[nodiscard]] Mode getMode() const = 0;
	};
}