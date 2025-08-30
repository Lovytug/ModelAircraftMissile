#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../IGuidanceHeadRealisticPhisics.h"
#include "../../../../../../../algorithm/IBaseAlgorithm.h"

namespace mml {
	class Vector;
}

namespace phis
{
	struct GuidanceHeadDynamicBundle final : public mdt::DynamicBundle
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


	class MyGuidanceHeadRealisticPhisics final : public IGuidanceHeadRealisticPhisics
	{
	public:
		MyGuidanceHeadRealisticPhisics(u_ptr<alg::IBaseAlgorithm>);

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] mml::Vector compute_acceleration_command(const detail::IDataProvider&, mml::Vector r_rel, mml::Vector V_rel) const noexcept;

	private:
		u_ptr<alg::IBaseAlgorithm> algorithm;
	};
}