#pragma once
#include "ICombustionChamber.h"

namespace chamb
{
	template<typename IFace = ICombustionChamber>
	struct MyCombustionChamberDynamicData final : public detail::IComponent::DynamicType
	{
		MyCombustionChamberDynamicData(
			double pressure, double mass_gaze, double V_cam
		) {
			set<IFace>("pressure", pressure);
			set<IFace>("mass_gaze", mass_gaze);
			set<IFace>("V_cam", V_cam);
		}
	};

	template<typename IFace = ICombustionChamber>
	struct MyCombustionChamberStaticData final : public detail::IComponent::StaticType
	{
		MyCombustionChamberStaticData(
			const double R_g, const std::string name
		) {
			set<IFace>("R_g", R_g);
			set<IFace>("name", name);
		}
	};
	
	class MyCombustionChamber final : public ICombustionChamber
	{
	public:
		explicit MyCombustionChamber(
			u_ptr<phis::IPhisicsModule> phisics,
			double start_pressure, double V_cam,
			double R_g, std::string name
		);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscatd]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyCombustionChamberDynamicData<> dyn_data;
		MyCombustionChamberStaticData<> stat_data;
	};
}