#pragma once
#include "INozzle.h"

namespace nuz
{
	class MyNuzzle : public INuzzle
	{
	public:
		explicit MyNuzzle(IDataProvider& sensor_pressure, IDataProvider& sensor_comb_temp,
			double critical_area_nuzzle, double adiabatic_index, double R_g, std::string name);

		void update(float dt) override;

		[[nodiscard]] std::vector<double> getVectorState() const override;
		[[nodiscard]] double getThrust() const override;
		[[nodiscard]] double getMassFlowRate() const override;
		[[nodiscard]] std::string getName() const override;

	private:
		[[nodiscard]] float get_P const;
		[[nodiscard]] float get_P_crit const;

	private:
		double mass_flow_rate;
		double thrust;

		const IDataProvider& sensor_pressure;
		const IDataProvider& sensor_combustion_temperature;
		const double critical_area_nuzzle;
		const double adiabatic_index;
		const double R_g;

		const std::string name;
	};
}