#pragma once
#include <vector>
#include <cmath>
#include "trapz.h"
#include "../../../../../../rocket/engine/fuel/fuel_profile/IFuelProfile.h"
#include "../../../../../realistic/IRealisticPhisicsModule.h"

namespace phis
{
	struct FuelProfileDynamicBundle : public DynamicBundle
	{
		std::function<double(const fuel::IFuelModel&)> area_func;
		std::function<double(const fuel::IFuelModel&, double)> dr_inner_func;
	};

	class StarProfileRealisticPhisics : IRealisticPhisicsModule
	{
	public:
		StarProfileRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_area(const fuel::IFuelProfile&);
		[[nodiscard]] double compute_dr_inner(const fuel::IFuelProfile& , const double);
		[[nodiscard]] double compute_perimeter(const fuel::IFuelProfile&) const;
		[[nodiscard]] double compute_base_profile(const fuel::IFuelProfile&, double) const;
		[[nodiscard]] double compute_derivity_base_profile(const fuel::IFuelProfile&, double) const;
	};
}