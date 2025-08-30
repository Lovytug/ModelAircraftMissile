#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../IPressureModelComputationRealisticPhisics.h"

namespace phis
{
	struct PressureModelComputationDynamicBundle final : public mdt::DynamicBundle
	{
		std::unordered_map<std::string, std::function<std::any(const std::vector<std::any>&)>> storage;

		std::any do_call(const std::string& name, const std::vector<std::any>& args) override {
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

	class MyPressureModelComputationRealisticPhisics final : public IPressureModelComputationRealisticPhisics
	{
	public:
		explicit MyPressureModelComputationRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		double compute_pressure(const detail::IComputeModule&, double) const;
	};
}