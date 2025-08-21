#pragma once
#include <functional>
#include "../../../../util/IComponent/IComponent.h"
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/nozzle/INozzle.h"

namespace phis
{
	struct NozzleDynamicBundle final : public DynamicBundle
	{
		std::unordered_map<std::string, std::function<double(const std::vector<std::any>&)>> storage;

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

	class NozzleRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		NozzleRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_mass_gaz_rate(const IComponent&, double) const noexcept;
		[[nodiscard]] double compute_F_thrust(const IComponent&, double) const noexcept;
		[[nodiscard]] inline double get_P(double) const noexcept;
		[[nodiscard]] inline double get_P_crit(double) const noexcept;
	};
}