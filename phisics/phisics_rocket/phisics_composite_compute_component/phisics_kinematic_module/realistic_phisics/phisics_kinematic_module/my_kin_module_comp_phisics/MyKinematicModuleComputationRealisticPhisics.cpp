#include "MyKinematicModuleComputationRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/kinematic_module/kinematic_module/IKinematicModuleComputation.h"
#include "../../../../../../../rocket/composite_compute_component/kinematic_module/linear_movement/ILinearMovementComputation.h"
#include "../../../../../../../rocket/composite_compute_component/kinematic_module/rotational_movement/IRotationalMovementComputation.h"

#include "../../../../../../../math_lib/Vector/Vector.h"
#include "../../../../../../../math_lib/integrtator/runge_kutta.h"
#include "../../../../../../../math_lib/integrtator/util/state_macro.h"

phis::MyKinematicModuleComputationRealisticPhisics::MyKinematicModuleComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyKinematicModuleComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<KinematicModuleComputationDynamicBundle>();

	bundle->add<detail::IComputeModule::DynamicType, const detail::IComputeModule&, mml::Vector>(
		"pos_func",
		[this](const detail::IComputeModule& computer, mml::Vector vec_vel) -> detail::IComputeModule::DynamicType {
			return compute_pos_func(computer, vec_vel);
		}
	);

	bundle->add<detail::IComputeModule::DynamicType, const detail::IComputeModule&, mml::Vector>(
		"quaternion_orientation_func",
		[this](const detail::IComputeModule& computer, mml::Vector vec_omega) -> detail::IComputeModule::DynamicType {
			return compute_quaternion_orientation_func(computer, vec_omega);
		}
	);

	return bundle;
}

detail::IComputeModule::DynamicType phis::MyKinematicModuleComputationRealisticPhisics::compute_quaternion_orientation_func(const detail::IComputeModule& computer, mml::Vector vec_omega) const
{
	auto provider_rotation = computer.getProvider<comp::IRotationalMovementComputation>();

	auto bundle_rotation = provider_rotation->getPhisicsFunc();

	auto quaternion_orientation_func = bundle_rotation->call<detail::IComputeModule::DynamicType>("quaternion_orientation_func");

	return quaternion_orientation_func(*provider_rotation, vec_omega);
}

detail::IComputeModule::DynamicType phis::MyKinematicModuleComputationRealisticPhisics::compute_pos_func(const detail::IComputeModule& computer, mml::Vector vec_vel) const
{
	auto provider_linear = computer.getProvider<comp::ILinearMovementComputation>();

	auto bundle_linear = provider_linear->getPhisicsFunc();

	auto pos_func = bundle_linear->call<detail::IComputeModule::DynamicType>("pos_func");

	return pos_func(*provider_linear, vec_vel);
}