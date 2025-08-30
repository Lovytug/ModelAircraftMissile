#include "MyGuidanceHeadComputationRealisticPhisics.h"

#include "../../../../../../../rocket/composite_compute_component/homing_system/guidance_head/guidance_head/IGuidanceHeadComputation.h"

#include "../../../../../../../rocket/simple_component/homing_system/guidance head/IGuidanceHead.h"

#include "../../../../../../../math_lib/Vector/Vector.h"

phis::MyGuidanceHeadComputationRealisticPhisics::MyGuidanceHeadComputationRealisticPhisics() {}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyGuidanceHeadComputationRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<GuidanceHeadComputationDynamicBundle>();

	bundle->add<mml::Vector, const detail::IComputeModule&, mml::Vector, mml::Vector>(
		"guidance_head_func",
		[this](const detail::IComputeModule& computer, mml::Vector r_rel, mml::Vector V_rel) -> mml::Vector {
			return compute_guidance_head_func(computer, r_rel, V_rel);
		}
	);
	
	return bundle;
}

mml::Vector phis::MyGuidanceHeadComputationRealisticPhisics::compute_guidance_head_func(const detail::IComputeModule& computer, mml::Vector r_rel, mml::Vector V_rel) const
{
	auto provider_guidance = computer.getProvider<comp::IGuidanceHeadComputation>();

	auto bundle_guidance = provider_guidance->getPhisicsFunc();

	auto acc_command_func = bundle_guidance->call<mml::Vector>("acceleration_command_func");

	return acc_command_func(computer, r_rel, V_rel);
}
