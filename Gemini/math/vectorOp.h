#pragma once
#include "vector.h"
#include <math.h>

namespace gem::vector
{
	template<CStorableType T>
	inline T dot(const TVector<T>& v1, const TVector<T>& v2)
	{
		return (v1 * v2).sum();
	}

	template<CStorableType T>
	inline TVector<T> cross(const TVector<T>& v1, const TVector<T>& v2)
	{
		GEM_ASSERT(v1.length() == 3 && v2.length() == 3, "Cross product is defined only for 3D vectors");

		TVector<T> result(3);

		result[0] = v1[1] * v2[2] - v1[2] * v2[1];
		result[1] = v1[2] * v2[0] - v1[0] * v2[2];
		result[2] = v1[0] * v2[1] - v1[1] * v2[0];

		return result;
	}
}