#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<class T>
	constexpr bool is_array_impl = false;
	template<class T, size_t Size>
	constexpr bool is_array_impl<::std::array<T, Size>> = true;

	template<class T>
	constexpr bool is_subrange_impl = false;
	template<class Iterator, class Sequence, ::std::ranges::subrange_kind Kind>
	constexpr bool is_subrange_impl<::std::ranges::subrange<Iterator, Sequence, Kind>> = true;

	template<class T>
	constexpr bool is_tuple_impl = false;
	template<class... Ts>
	constexpr bool is_tuple_impl<::std::tuple<Ts...>> = true;

	template<class T>
	constexpr bool is_pair_impl = false;
	template<class First, class Second>
	constexpr bool is_pair_impl<::std::pair<First, Second>> = true;

	template<class T>
	constexpr bool tuple_like_impl()
	{
		using object_type = type_traits::object_t<T>;
		return is_pair_impl<object_type> || is_pair_impl<object_type> || is_array_impl<object_type> || is_subrange_impl<object_type>;
	}

}

template<class T>
concept tuple_like = detail::tuple_like_impl<T>();


NGS_LIB_END