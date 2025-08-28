#pragma once
#include <string>
#include "../IFuelProfile.h"

namespace fuel
{
	template<typename IFace = IFuelProfile>
	struct StarProfileDynamicData final : public detail::IComponent::DynamicType
	{
		StarProfileDynamicData(double area, double r_inner, Mode currentMode) {
			set<IFace>("area", area);
			set<IFace>("r_inner", r_inner);
			set<IFace>("currentMode", currentMode);
		}
	};

	template<typename IFace = IFuelProfile>
	struct StarProfileStaticData final : public detail::IComponent::StaticType
	{
		StarProfileStaticData(
			const double R_o, const double L_boost, const double L_sustain,
			const short N, const double Amp, const double theta, const std::string name
		) {
			set<IFace>("R_o", R_o);
			set<IFace>("L_boost", L_boost);
			set<IFace>("L_sustain", L_sustain);
			set<IFace>("N", N);
			set<IFace>("Amp", Amp);
			set<IFace>("theta", theta);
			set<IFace>("name", name);
		}
	};

	class StarProfile final : public IFuelProfile
	{
	public:
		explicit StarProfile(u_ptr<phis::IPhisicsModule> phisics, 
			double R_o, double R_i_0, double L_boost, double L_sustain,
			short N, double amp, double tetta, std::string name);

		void updateState(const DynamicType&) override;

		[[nodiscard]] const DynamicType& getDynamicData() const noexcept override;
		[[nodiscard]] const StaticType& getStaticData() const noexcept override;
		[[nodiscard]] u_ptr<mdt::DynamicBundle> getPhisicsFunc() const noexcept override;

	private:
		u_ptr<phis::IPhisicsModule> phisics;
		StarProfileDynamicData<> dyn_data;
		StarProfileStaticData<> stat_data;
	};
}