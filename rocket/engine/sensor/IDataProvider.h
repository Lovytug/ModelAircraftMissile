#pragma once

namespace sensor
{
	class IDataProvider
	{
	public:
		virtual ~IDataProvider() = default;
		virtual [[nodiscard]] double readValue() const = 0;
	};
}