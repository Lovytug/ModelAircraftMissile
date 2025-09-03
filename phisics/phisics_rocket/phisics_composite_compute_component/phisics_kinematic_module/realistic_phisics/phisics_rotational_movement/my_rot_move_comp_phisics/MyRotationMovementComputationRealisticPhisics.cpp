#include "MyRotationMovementComputationRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/kinematic_module/rotational_movement/IRotationalMovementComputation.h"

#include "../../../../../../../rocket/simple_component/kinematic_module/rotational_movement/IRotationalMovement.h"

#include "../../../../../../../math_lib/Vector/Vector.h"
#include "../../../../../../../math_lib/integrtator/runge_kutta.h"
#include "../../../../../../../math_lib/integrtator/util/state_macro.h"

DEFINE_STATE(RotationMovementIntegrator, quaternion_orientation_w, quaternion_orientation_x, quaternion_orientation_y, quaternion_orientation_z)

phis::MyRotationMovementComputationRealisticPhisics::MyRotationMovementComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyRotationMovementComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<RotationMovementComputationDynamicBundle>();

	bundle->add<detail::IComputeModule::DynamicType, const detail::IComputeModule&, mml::Vector>(
		"quaternion_orientation_func",
		[this](const detail::IComputeModule& computer, mml::Vector vec_omega) -> detail::IComputeModule::DynamicType {
			return compute_quaternion_orientation(computer, vec_omega);
		}
	);

	return bundle;
}

detail::IComputeModule::DynamicType phis::MyRotationMovementComputationRealisticPhisics::compute_quaternion_orientation(const detail::IComputeModule& computer, mml::Vector vec_omega) const
{
	auto [omega_x, omega_y, omega_z] = vec_omega;

	auto provider_rotation = computer.getProvider<kin_rot::IRotationalMovement>();

	auto bundle_rotation = provider_rotation->getPhisicsFunc();

	auto dquater_w_func = bundle_rotation->call<double>("dquaternion_orientation_w_func");
	auto dquater_x_func = bundle_rotation->call<double>("dquaternion_orientation_x_func");
	auto dquater_y_func = bundle_rotation->call<double>("dquaternion_orientation_y_func");
	auto dquater_z_func = bundle_rotation->call<double>("dquaternion_orientation_z_func");

	RotationMovementIntegrator state;
	state.quaternion_orientation_w = provider_rotation->getDynamicData().get<kin_rot::IRotationalMovement>("quaternion_orientation_w");
	state.quaternion_orientation_x = provider_rotation->getDynamicData().get<kin_rot::IRotationalMovement>("quaternion_orientation_x");
	state.quaternion_orientation_y = provider_rotation->getDynamicData().get<kin_rot::IRotationalMovement>("quaternion_orientation_y");
	state.quaternion_orientation_z = provider_rotation->getDynamicData().get<kin_rot::IRotationalMovement>("quaternion_orientation_z");

	auto derivs = [this](const RotationMovementIntegrator& s) -> RotationMovementIntegrator {
		RotationMovementIntegrator ds;
		ds.quaternion_orientation_w = dquater_w_func(*provider_rotation, omega_x, omega_y, omega_z);
		ds.quaternion_orientation_x = dquater_x_func(*provider_rotation, omega_x, omega_y, omega_z);
		ds.quaternion_orientation_y = dquater_y_func(*provider_rotation, omega_x, omega_y, omega_z);
		ds.quaternion_orientation_z = dquater_z_func(*provider_rotation, omega_x, omega_y, omega_z);
		return ds;
		};

	auto new_state = rk4_step(derivs, state, computer.getTime()->current(), computer.getTime()->dt());

	detail::IComputeModule::DynamicType result;
	result.set<kin_rot::IRotationalMovement>("quaternion_orientation_w", new_state.quaternion_orientation_w);
	result.set<kin_rot::IRotationalMovement>("quaternion_orientation_x", new_state.quaternion_orientation_x);
	result.set<kin_rot::IRotationalMovement>("quaternion_orientation_y", new_state.quaternion_orientation_y);
	result.set<kin_rot::IRotationalMovement>("quaternion_orientation_z", new_state.quaternion_orientation_z);

	return result;
}