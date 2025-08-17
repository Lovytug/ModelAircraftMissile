#pragma once

namespace fuel
{
	enum class Mode { Boost, Sustain };

	class IModeObserver
	{
	public:
		virtual ~IModeObserver() = default;
		virtual void OnModeChanged(Mode newMode) = 0;
	};
}