#pragma once

#include "math/vector.h"
#include "math/matrix.h"
#include "math/tensor.h"

#include "math/vectorOp.h"
#include "math/matrixOp.h"

namespace gem
{
	using Vectorf = TVector<f32>;
	using Vectord = TVector<f64>;

	using Matrixf = TMatrix<f32>;
	using Matrixd = TMatrix<f64>;

	using Tensor3f = TTensor3<f32>;
	using Tensor3d = TTensor3<f64>;

	using Tensor4f = TTensor4<f32>;
	using Tensor4d = TTensor4<f64>;
}