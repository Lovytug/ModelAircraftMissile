#pragma once
#include <memory>
#include <functional>
#include <cmath>
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/fuel/IFuelModel.h"
#include "../../../../util/IComponent/IComponent.h"

namespace phis
{
	struct FuelModelDynamicBundle : public DynamicBundle
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

	class FuelModelRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		FuelModelRealisticPhisics();
		
		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_burn_rate(const IComponent&, double) const;
		double compute_mass_flow_rate(const IComponent&, double, double) const;
	};
}