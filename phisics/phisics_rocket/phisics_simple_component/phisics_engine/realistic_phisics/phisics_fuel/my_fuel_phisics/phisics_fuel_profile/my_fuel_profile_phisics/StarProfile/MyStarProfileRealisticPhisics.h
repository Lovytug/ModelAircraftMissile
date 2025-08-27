#pragma once
#include <any>
#include <unordered_map>
#include "../../../../../../../../../../rocket/simple_component/engine/fuel/fuel_profile/IFuelProfile.h"
#include "../../IFuelProfileRealisticPhisiscs.h"

namespace phis
{
	struct FuelProfileDynamicBundle : public mdt::DynamicBundle
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

	class MyStarProfileRealisticPhisics final : public IFuelProfileRealisticPhisics
	{
	public:
		MyStarProfileRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_area(const detail::IDataProvider&);
		[[nodiscard]] double compute_dr_inner(const detail::IDataProvider& , const double);
		[[nodiscard]] double compute_perimeter(const detail::IDataProvider&) const;
		[[nodiscard]] double compute_base_profile(const detail::IDataProvider&, double) const;
		[[nodiscard]] double compute_derivity_base_profile(const detail::IDataProvider&, double) const;
	};
}