#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../ICombustionChamberComputationRealisticPhisics.h"

namespace phis
{
	struct CombustionChamberComputationDynamicBundle final : public mdt::DynamicBundle 
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

	class MyCombustionChamberComputationRealisticPhisics final : public ICombustionChamberComputationRealisticPhisics
	{
	public:
		explicit MyCombustionChamberComputationRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_dP_for_integrate(const detail::IComputeModule&, double, double) const;
	};
}
