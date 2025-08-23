#pragma once
#include "../../../../composables/IComputeModule.h"
#include "../../../realistic/IRealisticPhisicsModule.h"

namespace phis
{
	struct CombustionChamberComputationDynamicBundle final : public DynamicBundle 
	{
		std::unordered_map<std::string, std::function<std::any(const std::vector<std::any>&)>> storage;

		double do_call(const std::string& name, const std::vector<std::any>& args) override {
			auto it = storage.find(name);
			if (it == storage.end()) {
				throw std::runtime_error("Function not found: " + name);
			}
			return it->second(args);
		}

		void do_add(const std::string& name, std::function<double(const std::vector<std::any>&)> func) override {
			storage[name] = std::move(func);
		}
	};

	class CombustionChamberComputationRealisticPhisics final : public IRealisticPhisicsModule
	{
	public:
		explicit CombustionChamberComputationRealisticPhisics();

		[[nodiscard]] u_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_dP_for_integrate(const comp::IComputeModule&, double, double);
	};
}
