#pragma once

#include "./scalar.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct matrix_trait {};

template<class T>
	requires
	::std::ranges::contiguous_range<T>
	&& ::std::ranges::contiguous_range<::std::ranges::range_value_t<T>>
	&& (stl::ranges::algorithm::static_size<T>() > 0)
	&& (stl::ranges::algorithm::static_size<::std::ranges::range_value_t<T>>() > 0)
struct matrix_trait<T>
{
	using value_type = type_traits::naked_t<::std::ranges::range_value_t<::std::ranges::range_value_t<T>>>;
	constexpr static auto major() { return stl::ranges::algorithm::static_size<T>(); }
	constexpr static auto minor() { return stl::ranges::algorithm::static_size<::std::ranges::range_value_t<T>>(); }
};

template<class T>
concept matrix = 
	::std::ranges::contiguous_range<T>
	&& ::std::ranges::contiguous_range<::std::ranges::range_value_t<T>>
	&& scalar<typename matrix_trait<T>::value_type>
	&& (matrix_trait<T>::major() > 1 && matrix_trait<T>::major() < 5)
	&& (matrix_trait<T>::minor() > 1 && matrix_trait<T>::minor() < 5)
;

NGS_LIB_MODULE_END