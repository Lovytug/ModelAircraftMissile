#pragma once

namespace fuel
{
	class IFuelProfile()
	{
	public:
		~IFuelProfile() = default;
		virtual [[nodiscard]] double getBurnArea(const double area) const = 0;
	}
}