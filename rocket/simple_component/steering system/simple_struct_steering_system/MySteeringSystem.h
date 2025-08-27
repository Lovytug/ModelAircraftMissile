#pragma once
#include "ISteeringSystem.h"

namespace steer
{
	template<typename IFace = ISteeringSystem>
	struct MySteeringSystemDynamicData : public detail::IComponent::DynamicType
	{
		MySteeringSystemDynamicData(
			double delta_steering, double zeta_steering, 
			double delta_velocity_steering
		) {
			set<IFace>("delta_steering", delta_steering);
			set<IFace>("delta_velocity_steering", delta_velocity_steering);
			set<IFace>("zeta_steering", zeta_steering);
		}
	};

	template<typename IFace = ISteeringSystem>
	struct MySteeringSystemStaticData : public detail::IComponent::StaticType
	{
		MySteeringSystemStaticData(
			const double tau, const double delta_max_steering,
			const double damping_coef, const std::string name
		) {
			set<IFace>("tau", tau);
			set<IFace>("delta_max_steering", delta_max_steering);
			set<IFace>("damping_coef", damping_coef);
			set<IFace>("name", name);
		}
	};

	class MySteeringSystem : public ISteeringSystem
	{
	public:
		explicit MySteeringSystem(
			u_ptr<phis::IPhisicsModule> phisics,
			double tau, double delta_max_steering,
			double damping_coef, std::string name
		);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MySteeringSystemDynamicData<> dyn_data;
		MySteeringSystemStaticData<> stat_data;
	};
}