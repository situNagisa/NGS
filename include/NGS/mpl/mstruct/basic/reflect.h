#pragma once

#include "./field_data.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct reflect_functor{};

template<class T> requires requires{ { type_traits::object_t<T>::reflect() }; }
struct reflect_functor<T>
{
	static constexpr decltype(auto) apply()
	{
		return type_traits::object_t<T>::reflect();
	}
	constexpr decltype(auto) operator()()const { return apply(); }
};

template<class T>
concept reflectable = requires{ { reflect_functor<T>::apply() } -> field_data; };

NGS_LIB_MODULE_END