#include "MyGuidanceHead.h"

head::MyGuidanceHead::MyGuidanceHead() :
	phisics(std::move(phisics)) {}

void head::MyGuidanceHead::updateState(const DynamicType& state)
{
	dyn_data = state;
}

[[nodiscard]] const detail::IComponent::DynamicType& head::MyGuidanceHead::getDynamicData() const noexcept
{
	return dyn_data;
}

[[nodiscard]] const detail::IComponent::StaticType& head::MyGuidanceHead::getStaticData() const noexcept
{
	return stat_data;
}

[[nodiscard]] u_ptr<mdt::DynamicBundle> head::MyGuidanceHead::getPhisicsFunc() const noexcept
{
	return phisics->getDynamicBundle();
}