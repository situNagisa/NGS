#pragma once

#include "./size.h"
#include "./fundamental.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct vector_trait{};

template<class T>
	requires ::std::ranges::contiguous_range<T> && (_detail::size<T>::value > 0)
struct vector_trait<T>
{
	using value_type = type_traits::naked_t<::std::ranges::range_value_t<T>>;
	constexpr static auto dimension() { return _detail::size<T>::value; }
};

template<class T>
concept vector = ::std::ranges::contiguous_range<T> && fundamental<typename vector_trait<T>::value_type> && (vector_trait<T>::dimension() > 0 && vector_trait<T>::dimension() < 5);

NGS_LIB_MODULE_END