#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../ILinearMovementRealisticPhisics.h"

namespace phis
{
	struct LinearMovementDynamicBundle final : public mdt::DynamicBundle
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


	class MyLinearMovementRealisticPhisics final : public ILinearMovementRealisticPhisics
	{
	public:
		MyLinearMovementRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_pos_x(const detail::IDataProvider&, double) const noexcept;
		[[nodiscard]] double compute_pos_y(const detail::IDataProvider&, double) const noexcept;
		[[nodiscard]] double compute_pos_z(const detail::IDataProvider&, double) const noexcept;
	};
}