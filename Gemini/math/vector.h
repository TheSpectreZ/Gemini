#pragma once
#include "core/storage.h"

namespace gem
{
	template<CStorableType DataType>
	class TTensor1 : public TTensorStorage<DataType, 1>
	{
		using parent_class = TTensorStorage<DataType, 1>;
	public:
		TTensor1() = default;
		~TTensor1() override = default;

		TTensor1(u32 size)
		{
			parent_class::reset(size);
		}

		TTensor1(const NestedInitializerList<DataType, 1>::type& list)
		{
			*this = list;
		}

		TTensor1& operator=(const NestedInitializerList<DataType, 1>::type& list)
		{
			parent_class::reset((u32)list.size());

			u32 Iter = 0;
			for (auto& ele : list)
			{
				parent_class::at(Iter++) = ele;
			}

			return *this;
		}

		DataType& operator[](u32 Index) { return parent_class::at(Index); }
		
		const DataType& operator[](u32 Index) const { return parent_class::at(Index); }

		TTensor1 elementWiseOp(auto&& func) const
		{
			TTensor1<DataType> result((u32)parent_class::length());

			for (u32 Iter = 0; Iter < (u32)parent_class::length(); Iter++)
				result[Iter] = func(parent_class::at(Iter));

			return result;
		}

		TTensor1 elementWiseOp(const TTensor1& Other, auto&& func) const
		{
			GEM_ASSERT(parent_class::length() == Other.length(), "Vector length must be same for Element-Wise Operation");

			TTensor1<DataType> result((u32)parent_class::length());

			for (u32 Iter = 0; Iter < (u32)parent_class::length(); Iter++)
				result[Iter] = func(parent_class::at(Iter), Other.at(Iter));

			return result;
		}

		TTensor1 operator+(const DataType& Value) const
		{
			return elementWiseOp([Value](auto e) { return e + Value; });
		}
		
		TTensor1 operator-(const DataType& Value) const
		{
			return elementWiseOp([Value](auto e) { return e - Value; });
		}
		
		TTensor1 operator*(const DataType& Value) const
		{
			return elementWiseOp([Value](auto e) { return e * Value; });
		}
		
		TTensor1 operator/(const DataType& Value) const
		{
			GEM_ASSERT(Value != 0, "Cannot divide by zero");
			return elementWiseOp([Value](auto e) { return e / Value; });
		}

		TTensor1 operator+(const TTensor1& Other) const
		{
			return elementWiseOp(Other, [](auto e1, auto e2) { return e1 + e2; });
		}

		TTensor1 operator-(const TTensor1& Other) const
		{
			return elementWiseOp(Other, [](auto e1, auto e2) { return e1 - e2; });
		}
		
		TTensor1 operator*(const TTensor1& Other) const
		{
			return elementWiseOp(Other, [](auto e1, auto e2) { return e1 * e2; });
		}
		
		DataType sum() const
		{
			DataType result = DataType{ 0 };

			for (u32 Iter = 0; Iter < (u32)parent_class::length(); Iter++)
				result += parent_class::at(Iter);

			return result;
		}

		DataType norm() const
		{
			DataType result = DataType{ 0 };

			for (u32 Iter = 0; Iter < (u32)parent_class::length(); Iter++)
			{
				auto value = parent_class::at(Iter);
				result += value * value;
			}

			return gem::sqrt(result);
		}

		void normalize()
		{
			auto Norm = norm();

			for(u32 Iter = 0; Iter < (u32)parent_class::length(); Iter++)
			{
				parent_class::at(Iter) /= Norm;
			}
		}
	};

	template<CStorableType T>
	using TVector = TTensor1<T>;
}