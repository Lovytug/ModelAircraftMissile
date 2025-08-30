#pragma once
#include <iostream>
#include <unordered_map>
#include <any>
#include "../IRotationalMovementRealisticPhisics.h"

namespace phis
{
	struct RotationalMovementDynamicBundle final : public mdt::DynamicBundle
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


	class MyRotationalMovementRealisticPhisics final : public IRotationalMovementRealisticPhisics
	{
	public:
		MyRotationalMovementRealisticPhisics();

		[[nodiscard]] u_ptr<mdt::DynamicBundle> getDynamicBundle() const override;

	private:
		[[nodiscard]] double compute_dquaternion_orientation_w(const detail::IDataProvider&, double, double, double) const noexcept;
		[[nodiscard]] double compute_dquaternion_orientation_x(const detail::IDataProvider&, double, double, double) const noexcept;
		[[nodiscard]] double compute_dquaternion_orientation_y(const detail::IDataProvider&, double, double, double) const noexcept;
		[[nodiscard]] double compute_dquaternion_orientation_z(const detail::IDataProvider&, double, double, double) const noexcept;
	};
}