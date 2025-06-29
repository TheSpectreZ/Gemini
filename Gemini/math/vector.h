#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TVector : public TMatrixStorage<DataType, 1>
	{
		using parent_class = TMatrixStorage<DataType, 1>;
	public:
		TVector() = default;
		~TVector() override = default;

		TVector(u32 size)
		{
			parent_class::reset(size);
		}

		TVector(const NestedInitializerList<DataType, 1>::type& list)
		{
			*this = list;
		}

		TVector& operator=(const NestedInitializerList<DataType, 1>::type& list)
		{
			parent_class::reset( (u32)list.size() );

			u32 Iter = 0;
			for (auto& ele : list)
			{
				parent_class::at(Iter) = ele;
			}

			return *this;
		}

		DataType& operator[](u32 Index) { return parent_class::at(Index); }
		const DataType& operator[](u32 Index) const { return parent_class::at(Index); }
	};

	using Vectorf = TVector<f32>;
	using Vectord = TVector<f64>;
}