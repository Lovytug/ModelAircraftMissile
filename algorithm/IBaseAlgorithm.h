#pragma once
#include "guidance/util/template_type_vector.h"
#include "../type_data/bundle/DynamicBundle.h"

namespace alg
{
	class IBaseAlgorithm {
	public:
		virtual ~IBaseAlgorithm() = default;

		template<typename RVec, typename VVec>
		Vec3d algorithm(const RVec& R, const VVec& Vr) const noexcept {
			return call_algorithm(to_array3(R), to_array3(Vr));
		}

	protected:
		virtual Vec3d call_algorithm(Vec3d, Vec3d) const noexcept = 0;
	};
}