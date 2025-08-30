#pragma once
#include "ILinearMovement.h"

namespace kin_lin
{
	template<typename IFace = ILinearMovement>
	struct MyLinearMovementDynamicData final : public detail::IComponent::DynamicType
	{
		MyLinearMovementDynamicData(
			double pos_x, double pos_y, double pos_z
		) {
			set<IFace>("pos_x", pos_x);
			set<IFace>("pos_y", pos_y);
			set<IFace>("pos_z", pos_z);
		}
	};

	template<typename IFace = ILinearMovement>
	struct MyLinearMovementStaticData final : public detail::IComponent::StaticType
	{
		MyLinearMovementStaticData(
			const std::string name
		) {
			set<IFace>("name", name);
		}
	};

	class MyLinearMovement final : public ILinearMovement
	{
	public:
		explicit MyLinearMovement(
			u_ptr<phis::IPhisicsModule> phisics,
			double pos_x, double pos_y, double pos_z,
			std::string name
		);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;


	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyLinearMovementDynamicData<> dyn_data;
		MyLinearMovementStaticData<> stat_data;
	};
}