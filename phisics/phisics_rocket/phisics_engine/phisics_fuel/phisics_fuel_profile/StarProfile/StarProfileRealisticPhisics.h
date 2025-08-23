#pragma once
#include <vector>
#include <cmath>
#include "trapz.h"
#include "../../../../../../rocket/engine/fuel/fuel_profile/IFuelProfile.h"
#include "../../../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../util/IComponent/IComponent.h"

namespace phis
{
	struct FuelProfileDynamicBundle : public DynamicBundle
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

	class StarProfileRealisticPhisics : IRealisticPhisicsModule
	{
	public:
		StarProfileRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_area(const IComponent&);
		[[nodiscard]] double compute_dr_inner(const IComponent& , const double);
		[[nodiscard]] double compute_perimeter(const IComponent&) const;
		[[nodiscard]] double compute_base_profile(const IComponent&, double) const;
		[[nodiscard]] double compute_derivity_base_profile(const IComponent&, double) const;
	};
}