#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TMatrix2D : public TMatrixStorage<DataType, 2>
	{
		using parent_class = TMatrixStorage<DataType, 2>;
	public:
		TMatrix2D() = default;
		TMatrix2D(u32 row, u32 col) { parent_class::reset(row, col); }
		TMatrix2D(const NestedInitializerList<DataType, 2>::type& list) { *this = list; }

		~TMatrix2D() override = default;

		TMatrix2D& operator=(const NestedInitializerList<DataType, 2>::type& list)
		{
			u32 row = (u32)list.size();
			u32 col = (u32)(*list.begin()).size();

			parent_class::reset(row, col);

			u32 rowIter = 0;
			for (auto& row : list)
			{
				u32 Iter = 0;
				for (auto& ele : row)
				{
					parent_class::at(rowIter, Iter) = ele;
					Iter++;
				}
				rowIter++;
			}

			return *this;
		}
	};

	using Matrixf = TMatrix2D<f32>;
	using Matrixd = TMatrix2D<f64>;
}