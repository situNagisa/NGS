#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct reflect{};

template<class T> requires requires{ { type_traits::object_t<T>::reflect() }; }
struct reflect<T>
{
	static constexpr decltype(auto) apply()
	{
		return type_traits::object_t<T>::reflect();
	}
};

template<class T>
concept reflectable = requires{{ reflect<T>::apply() };};

NGS_LIB_MODULE_END