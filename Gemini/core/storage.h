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

		T&		 operator[](u64 Index)		 { return mData[Index]; }
		const T& operator[](u64 Index) const { return mData[Index]; }

		T*		 data()			{ return mData; }
		const T* data()   const { return mData; }

		u64		 length() const { return mLength; }
		u64		 size()   const { return mLength * sizeof(T); }

		void dump()
		{
			println("Buffer dump");
			for(u64 i = 0; i < mLength; i++)
			{
				println(mData[i]);
			}
			println("");
		}
	};

	template<CStorableType DataType, u32 Order>
	class TMatrixStorage
	{
		const u32 MatrixOrder = Order;

		TBuffer<DataType> mBuffer;

		TBuffer<u32> mDimensions;
		TBuffer<u64> mStrides;
	public:
		TMatrixStorage() = default;
		virtual ~TMatrixStorage() = default;

		TMatrixStorage(const TMatrixStorage& other)
		{
			*this = other;
		}
		
		TMatrixStorage& operator=(const TMatrixStorage& other)
		{
			mBuffer = other.mBuffer;
			mDimensions = other.mDimensions;
			mStrides = other.mStrides;
		}

		TMatrixStorage(TMatrixStorage&& other)
		{
			*this = std::move(other);
		}
		
		TMatrixStorage& operator=(TMatrixStorage&& other)
		{
			mBuffer = std::move(other.mBuffer);
			mDimensions = std::move(other.mDimensions);
			mStrides = std::move(other.mStrides);
		}

		template<typename... T> requires ((sizeof...(T) == Order) && (std::is_same_v<T, u32> && ...))
		void reset(T... dimensions)
		{
			mDimensions = { dimensions... };
			
			mStrides.reset(mDimensions.length());
			
			u64 stride = 1;
			for (i64 Iter = mDimensions.length() - 1; Iter >= 0; Iter--)
			{
				mStrides[Iter] = stride;
				stride *= mDimensions[Iter];
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

		DataType* data() { return mBuffer.data(); }
		const DataType* data() const { return mBuffer.data(); }

		u64 size()	 const { return mBuffer.size()	; }
		u64 length() const { return mBuffer.length(); }
		
		TBuffer<u32> dimension() const { return mDimensions; }
		TBuffer<u64> strides() const { return mStrides; }

		void dump()
		{
			mBuffer.dump();
		}
	};
}