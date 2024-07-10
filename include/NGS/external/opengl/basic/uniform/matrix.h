#pragma once

#include "./size.h"
#include "./fundamental.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct matrix_trait {};

template<class T>
	requires
	::std::ranges::contiguous_range<T>
	&& ::std::ranges::contiguous_range<::std::ranges::range_value_t<T>>
	&& (_detail::size<T>::value > 0)
	&& (_detail::size<::std::ranges::range_value_t<T>>::value > 0)
struct matrix_trait<T>
{
	using value_type = type_traits::naked_t<::std::ranges::range_value_t<::std::ranges::range_value_t<T>>>;
	constexpr static auto major() { return _detail::size<T>::value; }
	constexpr static auto minor() { return _detail::size<::std::ranges::range_value_t<T>>::value; }
};

template<class T>
concept matrix = 
	::std::ranges::contiguous_range<T>
	&& ::std::ranges::contiguous_range<::std::ranges::range_value_t<T>>
	&& fundamental<typename matrix_trait<T>::value_type>
	&& (matrix_trait<T>::major() > 1 && matrix_trait<T>::major() < 5)
	&& (matrix_trait<T>::minor() > 1 && matrix_trait<T>::minor() < 5)
;

NGS_LIB_MODULE_END