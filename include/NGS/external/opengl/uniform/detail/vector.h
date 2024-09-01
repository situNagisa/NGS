#pragma once

#include "./scalar.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct vector_trait{};

template<class T>
	requires ::std::ranges::contiguous_range<T> && stl::ranges::algorithm::static_sized_range<T> && (stl::ranges::algorithm::static_size<T>() > 0)
struct vector_trait<T>
{
	using value_type = type_traits::naked_t<::std::ranges::range_value_t<T>>;
	constexpr static auto dimension() { return stl::ranges::algorithm::static_size<T>(); }
};

template<class T>
concept vector = ::std::ranges::contiguous_range<T> && scalar<typename vector_trait<T>::value_type> && (vector_trait<T>::dimension() > 0 && vector_trait<T>::dimension() < 5);

NGS_LIB_MODULE_END