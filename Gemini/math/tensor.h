#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TTensor3 : public TTensorStorage<DataType, 3>
	{
		using parent_class = TTensorStorage<DataType, 3>;
	public:
		TTensor3() = default;
		TTensor3(u32 depth, u32 row, u32 col) { parent_class::reset(depth, row, col); }
		TTensor3(const NestedInitializerList<DataType, 3>::type& list) { *this = list; }

		~TTensor3() override = default;

		TTensor3& operator=(const NestedInitializerList<DataType, 3>::type& list)
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
	class TTensor4 : public TTensorStorage<DataType, 4>
	{
		using parent_class = TTensorStorage<DataType, 4>;
	public:
		TTensor4() = default;
		TTensor4(u32 d1, u32 d2, u32 d3, u32 d4) { parent_class::reset(d1, d2, d3, d4); }
		TTensor4(const NestedInitializerList<DataType, 4>::type& list) { *this = list; }

		~TTensor4() override = default;

		TTensor4& operator=(const NestedInitializerList<DataType, 4>::type& list)
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

}