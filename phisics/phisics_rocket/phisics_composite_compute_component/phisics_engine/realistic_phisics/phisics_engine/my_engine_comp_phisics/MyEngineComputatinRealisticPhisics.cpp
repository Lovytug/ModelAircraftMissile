#include "MyEngineComputatinRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/engine/nozzle/INozzleComputation.h"
#include "../../../../../../../rocket/composite_compute_component/engine/combustion_chamber/ICombustionChamberComputation.h"
#include "../../../../../../../rocket/composite_compute_component/engine/fuel/IFuelModelComputation.h"

#include "../../../../../../../rocket/simple_component/engine/nozzle/INozzle.h"
#include "../../../../../../../rocket/simple_component/engine/combustion_chamber/ICombustionChamber.h"
#include "../../../../../../../rocket/simple_component/engine/fuel/IFuelModel.h"
#include "../../../../../../../rocket/simple_component/engine/fuel/fuel_profile/IFuelProfile.h"

#include "../../../../../../../math_lib/integrtator/runge_kutta.h"
#include "../../../../../../../math_lib/integrtator/util/state_macro.h"

DEFINE_STATE(EngineIntegrtor, pressure, r_inner)

phis::MyEngineComputationRealisticPhisics::MyEngineComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyEngineComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<EngineComputationDynamicBundle>();

	bundle->add<detail::IComputeModule::DynamicType>(
		"engine_func",
		[this](const detail::IComputeModule& computer) {
			return compute_engine_func(computer);
		}
	)
}

detail::IComputeModule::DynamicType phis::MyEngineComputationRealisticPhisics::compute_engine_func(const detail::IComputeModule& computer) const
{
	auto provider_fuel_model = computer.getProvider<comp::IFuelModelComputation>();
	auto provider_nozzle_model = computer.getProvider<comp::INozzleComputation>();
	auto provider_chamber_model = computer.getProvider<comp::ICombustionChamberComputation>();


	auto bundle_fuel = provider_fuel_model->getPhisicsFunc();
	auto bundle_nozzle = provider_nozzle_model->getPhisicsFunc();
	auto bundle_chamber = provider_chamber_model->getPhisicsFunc();

	auto burn_rate_func = bundle_fuel->call<double>("burn_rate_func");
	auto dr_inner_func = bundle_fuel->call<double>("dr_inner_func");
	auto area_func = bundle_fuel->call<double>("area_func");
	auto mass_flow_rate_func = bundle_fuel->call<double>("mass_flow_rate_func");

	auto mass_gaz_rate_func = bundle_nozzle->call<double>("mass_gaze_rate_func");
	auto F_thrust_func = bundle_nozzle->call<double>("F_thrust_func");

	auto dP_func = bundle_chamber->call<double>("dP_func");

	EngineIntegrtor state;
	state.pressure= provider_chamber_model->getDynamicData().get<chamb::ICombustionChamber>("pressure");
	state.r_inner = provider_fuel_model->getDynamicData().get<fuel::IFuelProfile>("r_inner");

	auto derivs = [this](const EngineIntegrtor& s) -> EngineIntegrtor {
		EngineIntegrtor ds;
		double m_dot_f = mass_flow_rate_func(*provider_fuel_model, s.pressure);
		double m_dot_e = mass_gaz_rate_func(*provider_nozzle_model, s.pressure);
		ds.pressure = dP_func(*provider_chamber_model, m_dot_f, m_dot_e);
		ds.r_inner = dr_inner_func(*provider_fuel_model, burn_rate_func(*provider_fuel_model, s.pressure));
		return ds;
	};

	auto new_state = rk4_step(derivs, state, computer.getTime()->current(), computer.getTime()->dt());

	detail::IComputeModule::DynamicType result;
	double mass_flow_rate = mass_flow_rate_func(*provider_fuel_model, new_state.pressure);
	double burn_rate = burn_rate_func(*provider_fuel_model, new_state.pressure);

	result.set<fuel::IFuelModel>("burn_rate", burn_rate);
	result.set<fuel::IFuelModel>("mass_flow_rate", mass_flow_rate);
	result.set<fuel::IFuelProfile>("dr_inner", new_state.r_inner);
	result.set<fuel::IFuelProfile>("area", area_func(*provider_fuel_model));
	result.set<noz::INozzle>("mass_gaze_rate", mass_gaz_rate_func(*provider_nozzle_model, new_state.pressure));
	result.set<noz::INozzle>("F_thrust", F_thrust_func(*provider_nozzle_model, new_state.pressure));
	result.set<chamb::ICombustionChamber>("pressure", new_state.pressure);

	return result;
}