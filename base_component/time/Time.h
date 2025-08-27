#pragma once

namespace detail
{
	class Time
	{
	public:
		explicit Time(double start_time, double dt)
			: time_(start_time), dt_(dt) { }

		[[nodiscard]] double current() const noexcept { return time_; }
		[[nodiscard]] double dt() const noexcept { return dt_; }
		void advance() noexcept { time_ += dt_; }

	private:
		double time_;
		double dt_;
	};
}