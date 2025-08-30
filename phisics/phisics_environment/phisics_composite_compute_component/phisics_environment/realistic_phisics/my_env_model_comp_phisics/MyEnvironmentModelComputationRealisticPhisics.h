#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../IEnvironmentModelComputationRealisticPhisics.h"

namespace phis
{
	struct EnvironmentModelComputationDynamicBundle final : public mdt::DynamicBundle
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

	class MyEnvironmentModelComputationRealisticPhisics final : public IEnvironmentModelComputationRealisticPhisics
	{
	public:
		explicit MyEnvironmentModelComputationRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		detail::IComputeModule::DynamicType compute_environment(const detail::IComputeModule&, double) const;
	};
}