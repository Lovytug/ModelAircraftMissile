#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../IFuelModelComputationRealisticPhisics.h"

namespace phis
{
	struct FuelModelComputationDynamicBundle final : public mdt::DynamicBundle 
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

	class MyFuelModelComputationRealisticPhisics final : public IFuelModelComputationRealisticPhisics
	{
	public:
		explicit MyFuelModelComputationRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_burn_rate_func_for_integrate(const detail::IComputeModule&, double) const;
		double compute_mass_flow_rate_for_integrate(const detail::IComputeModule&, double) const;
		double compute_dr_inner_for_integrate(const detail::IComputeModule&, double) const;
		double compute_area_func(const detail::IComputeModule&) const;
	};
}