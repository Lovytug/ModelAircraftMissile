#pragma once
#include <memory>
#include <functional>
#include <cmath>
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/fuel/IFuelModel.h"

namespace phis
{
	struct FuelModelDynamicBundle : public DynamicBundle
	{
		std::function<double(const fuel::IFuelModel&, double)> burn_rate_func;
		std::function<double(const fuel::IFuelModel&, double)> mass_flow_rate_func;
		std::function<double()> area_func;
		std::function<double()> r_inner_func;
	};

	class FuelModelRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		FuelModelRealisticPhisics();
		
		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_burn_rate(const fuel::IFuelModel&, double) const;
		double compute_mass_flow_rate(const fuel::IFuelModel&, double) const;
	};
}