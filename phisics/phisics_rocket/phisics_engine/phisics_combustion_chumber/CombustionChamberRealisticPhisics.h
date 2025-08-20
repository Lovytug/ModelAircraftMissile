#pragma once
#include <functional>
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/combustion_chamber/ICombustionChamber.h"
namespace phis
{
	struct CombustionChamberDynamicBundle : public DynamicBundle
	{
		std::function<double(const fuel::ICombustionChamber&, double)> dp_func;
	};

	class CombustionChamberRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		CombustionChamberRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_dp(const ICombustionChamber&, double, double) const noexcept;

	};
}