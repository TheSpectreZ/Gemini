#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TTensor2 : public TTensorStorage<DataType, 2>
	{
		using parent_class = TTensorStorage<DataType, 2>;
	public:
		TTensor2() = default;
		TTensor2(u32 row, u32 col) { parent_class::reset(row, col); }
		TTensor2(const NestedInitializerList<DataType, 2>::type& list) { *this = list; }

		~TTensor2() override = default;

		TTensor2& operator=(const NestedInitializerList<DataType, 2>::type& list)
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
	
		DataType trace() const
		{
			GEM_ASSERT(parent_class::mShape[0] == parent_class::mShape[1], "Trace doesn't exist for non-square Matrix");

			DataType result = DataType{ 0 };
			for (u32 Iter = 0; Iter < parent_class::mShape[0]; Iter++)
				result += parent_class::at(Iter, Iter);

			return result;
		}

		TTensor2 transpose() const
		{
			TTensor2 result(parent_class::mShape[0], parent_class::mShape[1]);

			for (u32 rowIter = 0; rowIter < parent_class::mShape[0]; rowIter++)
			{
				for (u32 colIter = 0; colIter < parent_class::mShape[1]; colIter++)
				{
					result.at(colIter, rowIter) = parent_class::at(rowIter, colIter);
				}
			}

			return result;
		}
	
		TTensor2 elementWiseOp(auto&& func) const
		{
			TTensor2 result(parent_class::mShape[0], parent_class::mShape[1]);

			for (u32 rowIter = 0; rowIter < parent_class::mShape[0]; rowIter++)
			{
				for (u32 colIter = 0; colIter < parent_class::mShape[1]; colIter++)
				{
					result.at(rowIter, colIter) = func(parent_class::at(rowIter, colIter));
				}
			}

			return result;
		}

		TTensor2 elementWiseOp(const TTensor2& Other, auto&& func) const
		{
			GEM_ASSERT(parent_class::mShape == Other.shape(), "Matrix Dimension must be same for Element-Wise Operation");

			TTensor2 result(parent_class::mShape[0], parent_class::mShape[1]);

			for (u32 rowIter = 0; rowIter < parent_class::mShape[0]; rowIter++)
			{
				for (u32 colIter = 0; colIter < parent_class::mShape[1]; colIter++)
				{
					result.at(rowIter, colIter) = func(parent_class::at(rowIter, colIter), Other.at(rowIter, colIter));
				}
			}

			return result;
		}

		TTensor2 operator+(const DataType& Value) const
		{
			return elementWiseOp([Value](auto ele) { return ele + Value; });
		}
		
		TTensor2 operator-(const DataType& Value) const
		{
			return elementWiseOp([Value](auto ele) { return ele - Value; });
		}
		
		TTensor2 operator*(const DataType& Value) const
		{
			return elementWiseOp([Value](auto ele) { return ele * Value; });
		}
		
		TTensor2 operator/(const DataType& Value) const
		{
			GEM_ASSERT(Value != 0, "Cannot divide by zero");
			return elementWiseOp([Value](auto ele) { return ele / Value; });
		}

		TTensor2 operator+(const TTensor2& Other) const
		{
			return elementWiseOp(Other, [](auto e1, auto e2) { return e1 + e2; });
		}

		TTensor2 operator-(const TTensor2& Other) const
		{
			return elementWiseOp(Other, [](auto e1, auto e2) { return e1 - e2; });
		}

		TTensor2 operator*(const TTensor2& Other)const
		{
			u32 Arow = parent_class::shape()[0];	
			u32 Acol = parent_class::shape()[1];	
			
			u32 Brow = Other.shape()[0];			
			u32 Bcol = Other.shape()[1];			

			GEM_ASSERT(Acol == Brow, "Matrix multiplication valid only if A.columns == B.rows");
			
			auto Transpose = Other.transpose();

			TTensor2 result(Arow, Bcol);

			for (u32 i = 0; i < Arow; ++i)
			{
				for (u32 j = 0; j < Bcol; ++j)
				{
					DataType sum = DataType{ 0 };

					for (u32 k = 0; k < Acol; ++k)
						sum += parent_class::at(i, k) * Transpose.at(j, k); 

					result.at(i, j) = sum;
				}
			}

			return result;
		}
	};

	template<CStorableType T>
	using TMatrix = TTensor2<T>;
}