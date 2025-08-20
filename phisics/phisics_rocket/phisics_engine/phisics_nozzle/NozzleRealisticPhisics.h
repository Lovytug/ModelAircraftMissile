#pragma once
#include <functional>
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/nozzle/INozzle.h"

namespace phis
{
	struct NozzleDynamicBundle : public DynamicBundle
	{
		std::function<double(const noz::INozzle&, double)> mass_gaz_rate_func;
		std::function<double(const noz::INozzle&, double)> F_thrust_func;
	};

	class NozzleRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		NozzleRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_mass_gaz_rate(const noz::INozzle&, double) const noexcept;
		[[nodiscard]] double compute_F_thrust(const noz::INozzle&, double) const noexcept;
		[[nodiscard]] inline double get_P(double) const noexcept;
		[[nodiscard]] inline double get_P_crit(double) const noexcept;
	};
}