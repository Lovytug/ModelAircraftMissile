#pragma once
#include <functional>
#include "../../../realistic/IRealisticPhisicsModule.h"
#include "../../../../rocket/engine/combustion_chamber/ICombustionChamber.h"
#include "../../../../util/IComponent/IComponent.h"

namespace phis
{
	struct CombustionChamberDynamicBundle : public DynamicBundle
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

	class CombustionChamberRealisticPhisics : public IRealisticPhisicsModule
	{
	public:
		CombustionChamberRealisticPhisics();

		[[nodiscard]] std::unique_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_dP(const IComponent&, double, double) const noexcept;

	};
}