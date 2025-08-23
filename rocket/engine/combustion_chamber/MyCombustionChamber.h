#pragma once
#include "ICombustionChamber.h"

namespace chamb
{
	struct MyCombustionChamberDynamicData : public DynamicDataType
	{
		MyCombustionChamberDynamicData(
			double pressure, double mass_gaze, double V_cam
		) {
			set("pressure", pressure);
			set("mass_gaze", mass_gaze);
			set("V_cam", V_cam);
		}
	};

	struct MyCombustionChamberStaticData : public StaticDataType
	{
		MyCombustionChamberStaticData(
			const double R_g, const std::string name
		) {
			set("R_g", R_g);
			set("name", name);
		}
	};
	
	class MyCombustionChamber : public ICombustionChamber
	{
	public:
		explicit MyCombustionChamber(
			u_ptr<phis::IPhisicsModule> phisics,
			double start_pressure, double V_cam,
			double R_g, std::string name
		);

		void updateState(const MyCombustionChamberDynamicData&) override;

		[[nodiscard]] DynamicDataType& getDynamicData() const noexcept override;
		[[nodiscard]] StaticDataType& getStaticData() const noexcept override;
		[[nodiscatd]] u_ptr<DynamicBundle> getPhisicFunc() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		MyCombustionChamberDynamicData dyn_data;
		MyCombustionChamberStaticData stat_data;
	};
}