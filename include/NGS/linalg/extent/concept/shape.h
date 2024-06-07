#pragma once

#include "../trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept shape = requires(T t, traits::rank_t i)
{
	requires ::std::integral<traits::index_t<type_traits::object_t<T>>>;
	typename traits::size_t<type_traits::object_t<T>>;

	{ traits::rank<type_traits::object_t<T>>::value() } -> ::std::convertible_to<traits::rank_t>;
	{ traits::rank_dynamic<type_traits::object_t<T>>::value() } -> ::std::convertible_to<traits::rank_t>;
	{ traits::rank_adaptor<type_traits::object_t<T>>::value() } -> ::std::convertible_to<traits::rank_t>;

	{ traits::static_extent<type_traits::object_t<T>>::value(i) } -> ::std::convertible_to<traits::static_extent_t>;
	{ traits::extent(NGS_PP_PERFECT_FORWARD(t), i) } -> ::std::convertible_to<traits::index_t<type_traits::object_t<T>>>;
};

template<class T>
concept dynamic_shape = shape<T> && (traits::rank_dynamic<type_traits::object_t<T>>::value() > 0);

template<class T>
concept static_shape = shape<T> && (traits::rank_dynamic<type_traits::object_t<T>>::value() == 0) && (traits::rank_adaptor<type_traits::object_t<T>>::value() == 0);

template<class T>
concept adaptor_shape = shape<T> && (traits::rank_adaptor<type_traits::object_t<T>>::value() > 0);


NGS_LIB_MODULE_END