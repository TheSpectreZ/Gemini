#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TMatrix3D : public TMatrixStorage<DataType, 3>
	{
		using parent_class = TMatrixStorage<DataType, 3>;
	public:
		TMatrix3D() = default;
		TMatrix3D(u32 depth, u32 row, u32 col) { parent_class::reset(depth, row, col); }
		TMatrix3D(const NestedInitializerList<DataType, 3>::type& list) { *this = list; }

		~TMatrix3D() override = default;

		TMatrix3D& operator=(const NestedInitializerList<DataType, 3>::type& list)
		{
			auto& level1 = list;
			auto& level2 = *level1.begin();
			auto& level3 = *level2.begin();
			
			u32 s1 = (u32)level1.size();
			u32 s2 = (u32)level2.size();
			u32 s3 = (u32)level3.size();

			parent_class::reset(s1, s2, s3);

			u32 IterL1 = 0;
			for (auto& L2 : list)
			{
				u32 IterL2 = 0;
				for (auto& L3 : L2)
				{
					u32 IterL3 = 0;
					for (auto& ele : L3)
					{
						parent_class::at(IterL1, IterL2, IterL3++) = ele;
					}
					IterL2++;
				}
				IterL1++;
			}

			return *this;
		}
	};

	template<CStorableType DataType>
	class TMatrix4D : public TMatrixStorage<DataType, 4>
	{
		using parent_class = TMatrixStorage<DataType, 4>;
	public:
		TMatrix4D() = default;
		TMatrix4D(u32 d1, u32 d2, u32 d3, u32 d4) { parent_class::reset(d1, d2, d3, d4); }
		TMatrix4D(const NestedInitializerList<DataType, 4>::type& list) { *this = list; }

		~TMatrix4D() override = default;

		TMatrix4D& operator=(const NestedInitializerList<DataType, 4>::type& list)
		{
			auto& level1 = list;
			auto& level2 = *level1.begin();
			auto& level3 = *level2.begin();
			auto& level4 = *level3.begin();

			u32 s1 = (u32)level1.size();
			u32 s2 = (u32)level2.size();
			u32 s3 = (u32)level3.size();
			u32 s4 = (u32)level4.size();

			parent_class::reset(s1, s2, s3, s4);

			u32 IterL1 = 0;
			for (auto& L2 : list)
			{
				u32 IterL2 = 0;
				for (auto& L3 : L2)
				{
					u32 IterL3 = 0;
					for (auto& L4 : L3)
					{
						u32 IterL4 = 0;
						for (auto& element : L4)
						{
							parent_class::at(IterL1, IterL2, IterL3, IterL4++) = element;
						}
						IterL3++;
					}
					IterL2++;
				}
				IterL1++;
			}

			return *this;
		}
	};

	using Tensor3f = TMatrix3D<f32>;
	using Tensor3d = TMatrix3D<f64>;

	using Tensor4f = TMatrix4D<f32>;
	using Tensor4d = TMatrix4D<f64>;
}