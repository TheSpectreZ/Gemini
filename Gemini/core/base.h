#pragma once
#include "type.h"

#include <initializer_list>
#include <concepts>

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
}

// TEMP
#include <iostream>

#define print(msg) std::cout << msg
#define println(msg) std::cout << msg << std::endl