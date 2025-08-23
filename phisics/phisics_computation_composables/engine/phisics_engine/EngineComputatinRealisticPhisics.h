#pragma once
#include "../../../../composables/IComputeModule.h"
#include "../../../realistic/IRealisticPhisicsModule.h"

namespace phis
{
	struct EngineComputationDynamicBundle final : public DynamicBundle 
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

	class EngineComputatinRealisticPhisics final : public IRealisticPhisicsModule
	{
	public:
		explicit EngineComputatinRealisticPhisics();

		[[nodiscard]] u_ptr<DynamicBundle> getDynamicBundle() const override;

	private:
		DynamicDataType& compute_engine_func(const comp::IComputeModule&);
	};
}