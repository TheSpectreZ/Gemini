#pragma once
#include "type.h"

#include <initializer_list>
#include <concepts>

#include <math.h>
#include <memory.h>
#include <stdio.h>

#include <crtdbg.h>

#define GEM_MODULE_NAME "Gemini"

#ifdef _DEBUG

#define GEM_REPORT(msg, ...) _RPT_BASE(_CRT_ASSERT, __FILE__, __LINE__, GEM_MODULE_NAME, msg, __VA_ARGS__);

#define GEM_ASSERT(expr, msg) if(!(expr)) GEM_REPORT("%s - %s", #expr, msg)
#define GEM_ASSERT_MSG(expr, msg, ...) if(!(expr)) GEM_REPORT("msg", __VA_ARGS__)

#else

#define GEM_REPORT(msg, ...)

#define GEM_ASSERT_E(expr)
#define GEM_ASSERT_M(expr, msg, ...) 
#define GEM_ASSERT_EM(expr, msg) 

#endif

namespace gem
{
	template<typename T>
	concept CStorableType = std::is_arithmetic_v<T>;

	template<CStorableType DataType, u32 N>
	struct NestedInitializerList
	{
		using type = std::initializer_list< typename NestedInitializerList<DataType,N-1>::type >;
	};

	template<CStorableType DataType>
	struct NestedInitializerList<DataType, 1>
	{
		using type = std::initializer_list<DataType>;
	};

	// TODO
	// Find faster alternatives

	template<CStorableType T>
	T min(T t1, T t2)
	{
		return t1 < t2 ? t1 : t2;
	}

	template<CStorableType T>
	T max(T t1, T t2)
	{
		return t1 > t2 ? t1 : t2;
	}

	template<CStorableType T>
	T abs(T value)
	{
		return value >= 0 ? value: -value;
	}

	template<CStorableType T>
	T sqrt(T value)
	{
		return (T)::sqrt((f64)value);
	}
}