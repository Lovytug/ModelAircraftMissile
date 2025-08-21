#pragma once
#include "../../realistic/IRealisticPhisicsModule.h"

namespace phis
{
	class EngineComputatinRealisticPhisics final : public IRealisticPhisicsModule
	{
	public:
		EngineComputatinRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		func()
	};
}