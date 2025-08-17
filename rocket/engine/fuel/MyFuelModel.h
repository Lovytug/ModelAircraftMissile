#pragma once
#include "IFuelModel.h"
#include "fuel_profile/IFuelProfile.h"

namespace fuel
{
	class MyFuelModel : public IFuelModel
	{
	public:
		explicit MyFuelModel(IFuelProfile& fuel_profile, IDataProvider& sensor,
			double fuel_density, float a_boost, float a_sustain,
			float n_boost, float n_sustain, std::string name);

		void update(double dt) override;

		[[nodiscard]] std::vector<double> getVectorState() const override;
		[[nodiscard]] double getMassFlowRate() const override;
		[[nodiscard]] std::string getName() const override;

		void OnModeChanged(Mode newMode) override;

	private:
		inline void updateTime(double dt);

		[[nodiscard]] double compute_burn_rate();
		[[nodiscard]] double compute_mass_flow_rate();

	private:
		Mode currentMode;

		double burn_rate;
		double mass_flow_rate;
		double time;
		IFuelProfile& profile;

		const IDataProvider& sensor_pressure;
		const double fuel_density;
		const float a_boost;
		const float a_sustain;
		const float n_boost;
		const float n_sustain;
		
		const std::string name;
	};
}