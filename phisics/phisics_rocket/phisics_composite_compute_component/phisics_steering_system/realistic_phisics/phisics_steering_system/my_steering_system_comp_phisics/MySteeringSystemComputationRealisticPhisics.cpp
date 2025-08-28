#include "MySteeringSystemComputationRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/steering_system/steering_system/ISteeringSystemComputation.h"

#include "../../../../../../../rocket/simple_component/steering system/simple_struct_steering_system/ISteeringSystem.h"

#include "../../../../../../../math_lib/integrtator/runge_kutta.h"
#include "../../../../../../../math_lib/integrtator/util/state_macro.h"

DEFINE_STATE(SteeringSystemIntegrtor, delta, zeta)

phis::MySteeringSystemComputationRealisticPhisics::MySteeringSystemComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MySteeringSystemComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<SteeringSystemComputationDynamicBundle>();

	bundle->add<detail::IComputeModule::DynamicType>(
		"steering_system_func",
		[this](const detail::IComputeModule& computer, double cmd) {
			return compute_steering_system_func(computer, cmd);
		}
	)
}

detail::IComputeModule::DynamicType phis::MySteeringSystemComputationRealisticPhisics::compute_steering_system_func(const detail::IComputeModule& computer, double cmd) const
{
	auto provider_steering = computer.getProvider<comp::ISteeringSystemComputation>();

	
	auto bundle_steer = provider_steering->getPhisicsFunc();
	
	auto ddelta_func = bundle_steer->call<double>("ddelta_func");
	auto dzeta_func = bundle_steer->call<double>("dzeta_func");

	SteeringSystemIntegrtor state;
	state.delta = provider_steering->getDynamicData().get<steer::ISteeringSystem>("delta_steering");
	state.zeta = provider_steering->getDynamicData().get<steer::ISteeringSystem>("zeta_steering");

	auto derivs = [this](const SteeringSystemIntegrtor& s) ->SteeringSystemIntegrtor {
		SteeringSystemIntegrtor ds;
		ds.delta = ddelta_func(*provider_steering);
		ds.zeta = dzeta_func(*provider_steering, cmd);
		return ds;
	};

	auto new_state = rk4_step(derivs, state, computer.getTime()->current(), computer.getTime()->dt());

	detail::IComputeModule::DynamicType result;

	result.set<steer::ISteeringSystem>("delta_steering", new_state.delta);
	result.set<steer::ISteeringSystem>("zeta_steering", new_state.zeta);

	return result;
}
