#pragma once
#include "IRotationalMovement.h"

namespace kin_rot
{
	template<typename IFace = IRotationalMovement>
	struct MyRotationalMovementDynamicData final : public detail::IComponent::DynamicType
	{
		MyLinearMovementDynamicData(
			double quaternion_orientation_w,
			double quaternion_orientation_x, 
			double quaternion_orientation_y, 
			double quaternion_orientation_z,
			double omega_x,
			double omega_y,
			double omega_z
		) {
			set<IFace>("quaternion_orientation_w", quaternion_orientation_w);
			set<IFace>("quaternion_orientation_x", quaternion_orientation_x);
			set<IFace>("quaternion_orientation_y", quaternion_orientation_y);
			set<IFace>("quaternion_orientation_z", quaternion_orientation_z);
			set<IFace>("omega_x", omega_x);
			set<IFace>("omega_y", omega_y);
			set<IFace>("omega_z", omega_z);
		}
	};

	template<typename IFace = IRotationalMovement>
	struct MyRotationalMovementStaticData final : public detail::IComponent::StaticType
	{
		MyLinearMovementStaticData(
			const std::string name
		) {
			set<IFace>("name", name);
		}
	};

	class MyRotationalMovement final : public IRotationalMovement
	{
	public:
		explicit MyRotationalMovement(
			u_ptr<phis::IPhisicsModule> phisics,
			double quaternion_orientation_w,
			double quaternion_orientation_x,
			double quaternion_orientation_y,
			double quaternion_orientation_z,
			double omega_x,
			double omega_y,
			double omega_z,
			std::string name
		);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyRotationalMovementDynamicData<> dyn_data;
		MyRotationalMovementStaticData<> stat_data;
	};
}