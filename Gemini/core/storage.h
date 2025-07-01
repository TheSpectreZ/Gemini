#pragma once
#include "base.h"

namespace gem
{
	template<typename T>
	struct TBuffer
	{
	protected:
		T*  mData = nullptr;
		u64 mLength = 0;
	public:
		TBuffer() = default;
		
		TBuffer(u64 length)
		{ 
			reset(length);
		}
				
		~TBuffer() 
		{ 
			clear();
		}

		TBuffer(const TBuffer& Other)
		{
			*this = Other;
		}

		TBuffer& operator=(const TBuffer& Other)
		{
			reset(Other.length());
			memcpy(mData, Other.data(), Other.size());
			return *this;
		}

		TBuffer(TBuffer&& Other)
		{
			*this = std::move(Other);
		}

		TBuffer& operator=(TBuffer&& Other)
		{
			clear();

			mData = Other.mData;
			mLength = Other.mLength;

			Other.mData = nullptr;
			Other.mLength = 0;

			return *this;
		}

		TBuffer(const std::initializer_list<T>& list)
		{
			*this = list;
		}

		TBuffer& operator=(const std::initializer_list<T>& list)
		{
			reset(list.size());

			u64 Iter = 0;
			for (auto& ele : list)
			{
				mData[Iter++] = ele;
			}

			return *this;
		}

		void clear()
		{
			if(mData) delete[] mData;
			mData = nullptr;
			mLength = 0;
		}

		void reset(u64 Length)
		{
			clear();

			mLength = Length;
			mData = new T[mLength];

			memset(mData, 0, size());
		}

		T& operator[](u64 Index)		 
		{ 
			GEM_ASSERT(Index < mLength, "Buffer Index out of Bounds");
			return mData[Index]; 
		}

		const T& operator[](u64 Index) const 
		{
			GEM_ASSERT(Index < mLength, "Buffer Index out of Bounds");
			return mData[Index]; 
		}

		T*		 data()			{ return mData; }
		const T* data()   const { return mData; }

		u64		 length() const { return mLength; }
		u64		 size()   const { return mLength * sizeof(T); }
	};

	class TensorShape
	{
		TBuffer<u32> mDimensions;
	public:
		TensorShape() = default;
		~TensorShape() = default;

		TensorShape(const std::initializer_list<u32>& dimensions)
			:mDimensions(dimensions) {}

		u64 length() const { return mDimensions.length(); }

		u32 operator[](u64 Index) const { return mDimensions[Index]; }

		bool operator ==(const TensorShape& other) const
		{
			if (length() != other.length())
				return false;
			
			for (u64 Iter = 0; Iter < length(); Iter++)
			{
				if (mDimensions[Iter] != other.mDimensions[Iter])
					return false;
			}

			return true;
		}

		bool operator != (const TensorShape& other) const 
		{
			return !operator==(other);
		}
	};

	template<CStorableType DataType, u32 Order>
	class TTensorStorage
	{
	protected:
		const u32 MatrixOrder = Order;
		TensorShape mShape;

		TBuffer<DataType> mBuffer;
		TBuffer<u64> mStrides;
	public:
		TTensorStorage() = default;
		virtual ~TTensorStorage() = default;

		TTensorStorage(const TTensorStorage& other)
		{
			*this = other;
		}
		
		TTensorStorage& operator=(const TTensorStorage& other)
		{
			mBuffer = other.mBuffer;
			mShape = other.mShape;
			mStrides = other.mStrides;
		}

		TTensorStorage(TTensorStorage&& other)
		{
			*this = std::move(other);
		}
		
		TTensorStorage& operator=(TTensorStorage&& other)
		{
			mBuffer = std::move(other.mBuffer);
			mShape = std::move(other.mShape);
			mStrides = std::move(other.mStrides);
		}

		template<typename... T> requires ((sizeof...(T) == Order) && (std::is_same_v<T, u32> && ...))
		void reset(T... dimensions)
		{
			mShape = { dimensions... };
			
			mStrides.reset(mShape.length());
			
			u64 stride = 1;
			for (i64 Iter = mShape.length() - 1; Iter >= 0; Iter--)
			{
				mStrides[Iter] = stride;
				stride *= mShape[Iter];
			}

			mBuffer.reset(stride);
		}

		template<typename... T> requires ((sizeof...(T) == Order) && (std::is_same_v<T, u32> && ...))
		DataType& at(T... dimensions)
		{
			u32 dims[] = { dimensions... };

			u64 Index = 0;
			for (u32 Iter = 0; Iter < Order; Iter++)
				Index = Index + dims[Iter] * mStrides[Iter];

			return mBuffer[Index];
		}
		
		template<typename... T> requires ((sizeof...(T) == Order) && (std::is_same_v<T, u32> && ...))
		const DataType& at(T... dimensions) const 
		{
			u32 dims[] = { dimensions... };

			u64 Index = 0;
			for (u32 Iter = 0; Iter < Order; Iter++)
				Index = Index + dims[Iter] * mStrides[Iter];

			return mBuffer[Index];
		}

		DataType* data() { return mBuffer.data(); }
		const DataType* data() const { return mBuffer.data(); }

		u64 size()	 const { return mBuffer.size()	; }
		u64 length() const { return mBuffer.length(); }
		
		const TensorShape& shape() const { return mShape; }
		const TBuffer<u64>& strides() const { return mStrides; }
	};

	template<template<typename, u32> typename T, typename DataType, u32 Order>
	concept CStorageContainer = CStorableType<DataType> && std::derived_from<T<DataType, Order>, TTensorStorage<DataType, Order>>;
}