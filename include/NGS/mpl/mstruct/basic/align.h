#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct struct_align {};
template<class T>
inline constexpr ::std::size_t struct_align_v = struct_align<T>::value;
template<class T>
using struct_align_t = typename struct_align<T>::type;

template<class T> requires requires
{
	{ type_traits::object_t<T>::align } -> ::std::convertible_to<::std::size_t>;
	requires layout::align<typename type_traits::object_t<T>::align_type>;
}
struct struct_align<T>
{
	using type = typename type_traits::object_t<T>::align_type;
	inline static constexpr ::std::size_t value = type_traits::object_t<T>::align;
};

NGS_LIB_MODULE_END