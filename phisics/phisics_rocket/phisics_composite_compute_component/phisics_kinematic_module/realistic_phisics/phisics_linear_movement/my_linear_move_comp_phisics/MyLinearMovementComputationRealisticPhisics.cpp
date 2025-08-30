#include "MyLinearMovementComputationRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/kinematic_module/linear_movement/ILinearMovementComputation.h"

#include "../../../../../../../rocket/simple_component/kinematic_module/linear_movement/ILinearMovement.h"

#include "../../../../../../../math_lib/Vector/Vector.h"
#include "../../../../../../../math_lib/integrtator/runge_kutta.h"
#include "../../../../../../../math_lib/integrtator/util/state_macro.h"

DEFINE_STATE(LinearMovementIntegrator, pos_x, pos_y, pos_z)

phis::MyLinearMovementComputationRealisticPhisics::MyLinearMovementComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyLinearMovementComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<LinearMovementComputationDynamicBundle>();

	bundle->add<detail::IComputeModule::DynamicType>(
		"pos_func",
		[this](const detail::IComputeModule& computer, mml::Vector vec_vel) -> detail::IComputeModule::DynamicType {
			return compute_pos(computer, vec_vel);
		}
	);

	return bundle;
}

detail::IComputeModule::DynamicType phis::MyLinearMovementComputationRealisticPhisics::compute_pos(const detail::IComputeModule& computer, mml::Vector vec_vel) const
{
	auto [Vx, Vy, Vz] = vec_vel;

	auto provider_linear = computer.getProvider<comp::ILinearMovementComputation>();

	auto bundle_linear = provider_linear->getPhisicsFunc();

	auto pos_x_func = bundle_linear->call<double>("pos_x_func");
	auto pos_y_func = bundle_linear->call<double>("pos_y_func");
	auto pos_z_func = bundle_linear->call<double>("pos_z_func");

	LinearMovementIntegrator state;
	state.pos_x = provider_linear->getDynamicData().get<kin_lin::ILinearMovement>("pos_x");
	state.pos_y = provider_linear->getDynamicData().get<kin_lin::ILinearMovement>("pos_y");
	state.pos_z = provider_linear->getDynamicData().get<kin_lin::ILinearMovement>("pos_z");

	auto derivs = [this](const LinearMovementIntegrator& s) ->LinearMovementIntegrator {
		LinearMovementIntegrator ds;
		ds.pos_x = pos_x_func(*provider_linear, Vx);
		ds.pos_y = pos_x_func(*provider_linear, Vy);
		ds.pos_z = pos_x_func(*provider_linear, Vz);
		return ds;
	};

	auto new_state = rk4_step(derivs, state, computer.getTime()->current(), computer.getTime()->dt());

	detail::IComputeModule::DynamicType result;
	result.set<kin_lin::ILinearMovement>("pos_x", new_state.pos_x);
	result.set<kin_lin::ILinearMovement>("pos_y", new_state.pos_y);
	result.set<kin_lin::ILinearMovement>("pos_z", new_state.pos_z);

	return result;
}