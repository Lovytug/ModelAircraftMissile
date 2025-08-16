#pragma once
#include "ICombustionChamber.h"

namespace chamb
{
	class MyCombustionChamber : public ICombustionChamber
	{
	public:
		explicit MyCombustionChamber(IDataProvider& sensorMassFlowRateFuel, IDataProvider& sensorMassFlowRateNuzzle,
			double adiabatiIndex, double R_g, std::string name);

		void update(float dt) override;

		std::vector<double> getVectorState() const override;
		[[nodiscard]] double getPressure() const override;
		[[nodiscard]] double getTemperature() const override;
		[[nodiscard]] std::string getName() const override;

	private:


	private:
		double pressure;
		double temperature;
		double mass_gaze;
		double V_cam;

		const IDataProvider& sensor_mass_flow_rate_fuel;
		const IDaraProvider& sensor_mass_flow_rate_nuzzle;
		const double adiabatic_index;
		const double R_g;

		const std::string name;
	};
}