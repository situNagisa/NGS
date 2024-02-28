#pragma once

#include "../field_data.h"
#include "./concept.h"
#include "./zero.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class, reflecter = zero_reflecter> struct reflect_functor{};

template<class T, reflecter Reflecter> requires requires{ { type_traits::object_t<T>::template reflect<Reflecter>() }; }
struct reflect_functor<T, Reflecter>
{
	static constexpr decltype(auto) apply()
	{
		return type_traits::object_t<T>::template reflect<Reflecter>();
	}
	constexpr decltype(auto) operator()()const { return apply(); }
};

template<class T, class Reflecter = zero_reflecter>
concept reflectable = reflecter<Reflecter> && requires{ { reflect_functor<T, Reflecter>::apply() } -> field_data; };

NGS_LIB_MODULE_END