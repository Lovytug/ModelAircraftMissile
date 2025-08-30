#include "MyGuidanceHeadRealisticPhisics.h"
#include "../../../../../../../math_lib/Vector/Vector.h"

phis::MyGuidanceHeadRealisticPhisics::MyGuidanceHeadRealisticPhisics(u_ptr<alg::IBaseAlgorithm> alg)
: algorithm(std::move(alg)) {}

[[nodiscard]] mml::Vector phis::MyGuidanceHeadRealisticPhisics::compute_acceleration_command(const detail::IDataProvider& head, mml::Vector r_rel, mml::Vector V_rel) const noexcept
{
	auto arr = algorithm->algorithm(std::move(r_rel), std::move(V_rel));
	mml::Vector v(std::begin(arr), std::end(arr));
	return v;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> phis::MyGuidanceHeadRealisticPhisics::getDynamicBundle() const
{
	auto bundle = std::make_unique<GuidanceHeadDynamicBundle>();

	bundle->add<mml::Vector, const detail::IDataProvider&, mml::Vector, mml::Vector>(
		"acceleration_command_func",
		[this](const detail::IDataProvider& steer, mml::Vector r_rel, mml::Vector V_rel) -> mml::Vector {
			return compute_acceleration_command(steer, r_rel, V_rel);
		}
	);

	return bundle;
}
