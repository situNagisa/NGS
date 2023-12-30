#pragma once

#include "./is_same_naked.h"
#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _T> struct storage { using type = _T; };
template<class _T> struct storage<_T&> { using type = ::std::add_pointer_t<_T>; };
template<class _T> struct storage<_T&&> { using type = ::std::add_pointer_t<::std::add_const_t<_T>>; };
template<class _T> struct storage<_T[]> { using type = ::std::add_pointer_t<_T>; };
template<class _T, size_t _N> struct storage<_T[_N]> { using type = ::std::add_pointer_t<_T>; };

template<class _T> using storage_t = typename storage<_T>::type;

template<class _T>
constexpr decltype(auto) store(auto&& value) requires is_same_naked_v<decltype(value), _T>
{
	if constexpr (::std::same_as<_T, storage_t<_T>>)
	{
		return NGS_PP_PERFECT_FORWARD(value);
	}
	else if constexpr (::std::is_reference_v<_T> || ::std::is_array_v<_T>)
	{
		return static_cast<storage_t<_T>>(::std::addressof(value));
	}
	else
	{
		static_assert(!::std::same_as<_T, _T>,
			"can't store _T"
			);
		return void();
	}
}

template<class _T>
constexpr decltype(auto) restore(auto&& value) requires is_same_naked_v<decltype(value), storage_t<_T>>
{
	if constexpr (::std::same_as<_T, storage_t<_T>>)
	{
		return NGS_PP_PERFECT_FORWARD(value);
	}
	else if constexpr (::std::is_reference_v<_T>)
	{
		return *value;
	}
	else if constexpr (::std::is_array_v<_T>)
	{
		return value;
	}
	else
	{
		static_assert(!::std::same_as<_T, _T>,
			"can't restore _T"
			);
		return void();
	}
}

NGS_TYPE_TRAIT_END