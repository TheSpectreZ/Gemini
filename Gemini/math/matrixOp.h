#pragma once
#include "matrix.h"

namespace gem::matrix
{
	template<CStorableType T>
	inline T L1Norm(const TMatrix<T>& matrix)
	{
		T result = T{ 0 };
		return result;
	}

	template<CStorableType T>
	inline T L2Norm(const TMatrix<T>& matrix)
	{
		T result = T{ 0 };
		return result;
	}

	template<CStorableType T>
	inline T LInfNorm(const TMatrix<T>& matrix)
	{
		T result = T{ 0 };
		return result;
	}
}