#pragma once
#include <unordered_map>
#include <any>
#include "../ICombustionChamberRealisticPhisics.h"

namespace phis
{
	struct CombustionChamberDynamicBundle final : public mdt::DynamicBundle
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

	class MyCombustionChamberRealisticPhisics final : public ICombustionChamberRealisticPhisics
	{
	public:
		MyCombustionChamberRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_dP(const detail::IDataProvider&, double, double) const noexcept;
	};
}