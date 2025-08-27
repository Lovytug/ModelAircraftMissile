#pragma once
#include <any>
#include <unordered_map>
#include "../IFuelModelRealisticPhisics.h"

namespace phis
{
	struct FuelModelDynamicBundle final : public mdt::DynamicBundle
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

	class MyFuelModelRealisticPhisics final : public IFuelModelRealisticPhisics
	{
	public:
		MyFuelModelRealisticPhisics();
		
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_burn_rate(const detail::IDataProvider&, double) const;
		double compute_mass_flow_rate(const detail::IDataProvider&, double, double) const;
	};
}