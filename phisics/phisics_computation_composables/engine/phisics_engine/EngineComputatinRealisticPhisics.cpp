#pragma once
#include "EngineComputatinRealisticPhisics.h"
#include "../../../../composables/computation/engine/fuel/IFuelModelComputation.h"
#include "../../../../composables/computation/engine/nozzle/INozzleComputation.h"
#include "../../../../composables/computation/engine/combustion_chamber/ICombustionChamberComputation.h"
#include "utility"
#include "runge_kutta";

phis::EngineComputatinRealisticPhisics::EngineComputatinRealisticPhisics() {}

DynamicDataType& phis::EngineComputatinRealisticPhisics::compute_engine_func(const comp::IComputeModule& computer)
{
	auto provider_fuel_model = computer.getProvider<comp::IFuelModelComputation>();
	auto provider_nozzle_model = computer.getProvider<comp::INozzleComputation>();
	auto provider_chamber_model = computer.getProvider<comp::ICombustionChamberComputation>();



	auto bundle_fuel = provider_fuel_model->getPhisicFunc();
	auto bundle_nozzle = provider_nozzle_model->getPhisicFunc();
	auto bundle_chamber = provider_chamber_model->getPhisicFunc();


	auto burn_rate_func = bundle_fuel->call<double>("burn_rate_func");
	auto dr_inner_func = bundle_fuel->call<double>("dr_inner_func");
	auto mass_flow_rate_func = bundle_fuel->call<double>("mass_flow_rate_func");

	auto mass_gaz_rate_func = bundle_nozzle->call<double>("mass_gaz_rate_func");
	auto F_thrust_func = bundle_nozzle->call<double>("F_thrust_func");

	auto dP_func = bundle_chamber->call<double>("dP_func");

	using State = std::pair<double, double>;
	State state = {
		provider_chamber_model->getDynamicData().get<DynamicDataType&>("")
		provider_fuel_model->getDynamicData().get<double>("dr_inner")
	};

	auto derivs = [this](const State& s) -> State {
		double m_dot_f = mass_flow_rate_func(provider_fuel_model, s.first);
		double m_dot_e = mass_gaz_rate_func(provider_nozzle_model, s.first);
		double dP = dP_func(provider_chamber_model, mass_flow_rate_func, mass_gaz_rate_func);
		double dr_inner = dr_inner_func(provider_fuel_model, burn_rate_func(provider_fuel_model, s.first));
		return { dP, dr_inner };
	};

	auto runge
}