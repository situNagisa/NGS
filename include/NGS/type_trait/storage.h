#pragma once

#include "./is_same_naked.h"
#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class _T> struct storage_trait
{
	using storage_type = _T;
	using restore_type = _T;
};
template<class _T> struct storage_trait<_T&>
{
	using storage_type = ::std::add_pointer_t<_T>;
	using restore_type = _T&;
};
template<class _T> struct storage_trait<_T&&>
{
	using storage_type = _T;
	using restore_type = _T;
};
template<class _T> struct storage_trait<_T[]>
{
	using storage_type = ::std::add_pointer_t<_T>;
	using restore_type = ::std::add_pointer_t<_T>;
};
template<class _T, size_t _N> struct storage_trait<_T[_N]>
{
	using storage_type = ::std::add_pointer_t<_T>;
	using restore_type = ::std::add_pointer_t<_T>;
};

template<class _T> using storage_t = typename storage_trait<_T>::storage_type;
template<class _T> using restored_t = typename storage_trait<_T>::restore_type;

template<class _T>
constexpr decltype(auto) store(auto&& value) requires is_same_naked_v<decltype(value), _T>
{
	using storage_type = storage_t<_T>;
	if constexpr (::std::is_lvalue_reference_v<_T> && ::std::same_as<::std::add_pointer_t<::std::remove_reference_t<_T>>, storage_type>)
	{
		return static_cast<storage_type>(::std::addressof(value));
	}
	else if constexpr (::std::is_rvalue_reference_v<_T> && ::std::same_as<::std::remove_reference_t<_T>, storage_type>)
	{
		return NGS_PP_PERFECT_FORWARD(value);
	}
	else if constexpr (::std::is_array_v<_T> && requires{ requires ::std::same_as<::std::add_pointer_t<::std::ranges::range_value_t<_T>>, storage_type>; })
	{
		return static_cast<storage_type>(value);
	}
	else
	{
		static_assert(::std::convertible_to<decltype(value), storage_type>, "can't store _T");
		return NGS_PP_PERFECT_FORWARD(value);
	}
}

template<class _T>
constexpr decltype(auto) restore(auto&& value) requires is_same_naked_v<decltype(value), storage_t<_T>>
{
	using restore_type = restored_t<_T>;
	if constexpr (::std::is_lvalue_reference_v<_T> && ::std::same_as<_T, restore_type>)
	{
		return static_cast<restore_type>(*value);
	}
	else if constexpr (::std::is_rvalue_reference_v<_T> && ::std::same_as<::std::remove_reference_t<_T>, restore_type>)
	{
		return static_cast<restore_type>(NGS_PP_PERFECT_FORWARD(value));
	}
	else if constexpr (::std::is_array_v<_T> && requires{ requires ::std::same_as<::std::add_pointer_t<::std::ranges::range_value_t<_T>>, restore_type>; })
	{
		return static_cast<restore_type>(NGS_PP_PERFECT_FORWARD(value));
	}
	else
	{
		static_assert(::std::convertible_to<decltype(value), restore_type>, "can't restore _T");
		return /*static_cast<restore_type>*/NGS_PP_PERFECT_FORWARD(value);
	}
}

NGS_TYPE_TRAIT_END