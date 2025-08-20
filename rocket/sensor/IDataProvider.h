#pragma once

namespace sensor
{
	class IDataProvider
	{
	public:
		virtual ~IDataProvider() = default;
		virtual [[nodiscard]] double read(double param) const = 0;
	};
}