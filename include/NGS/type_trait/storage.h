#pragma once

#include "./is_same_naked.h"
#include "./defined.h"

NGS_TYPE_TRAIT_BEGIN

template<class T> struct storage_trait
{
	using storage_type = T;
	using restore_type = T;
};
template<class T> struct storage_trait<T&>
{
	using storage_type = ::std::add_pointer_t<T>;
	using restore_type = T&;
};
template<class T> struct storage_trait<T&&>
{
	using storage_type = T;
	using restore_type = T;
};
template<class T> struct storage_trait<T[]>
{
	using storage_type = ::std::add_pointer_t<T>;
	using restore_type = ::std::add_pointer_t<T>;
};
template<class T, size_t N> struct storage_trait<T[N]>
{
	using storage_type = ::std::add_pointer_t<T>;
	using restore_type = ::std::add_pointer_t<T>;
};

template<class T> using storage_t = typename storage_trait<T>::storage_type;
template<class T> using restored_t = typename storage_trait<T>::restore_type;

template<class T>
constexpr decltype(auto) store(auto&& value) requires is_same_naked_v<decltype(value), T>
{
	using storage_type = storage_t<T>;
	if constexpr (::std::is_lvalue_reference_v<T> && ::std::same_as<::std::add_pointer_t<::std::remove_reference_t<T>>, storage_type>)
	{
		return static_cast<storage_type>(::std::addressof(value));
	}
	else if constexpr (::std::is_rvalue_reference_v<T> && ::std::same_as<::std::remove_reference_t<T>, storage_type>)
	{
		return NGS_PP_PERFECT_FORWARD(value);
	}
	else if constexpr (::std::is_array_v<T> && requires{ requires ::std::same_as<::std::add_pointer_t<::std::ranges::range_value_t<T>>, storage_type>; })
	{
		return static_cast<storage_type>(value);
	}
	else
	{
		static_assert(::std::convertible_to<decltype(value), storage_type>, "can't store T");
		return NGS_PP_PERFECT_FORWARD(value);
	}
}

template<class T>
constexpr decltype(auto) restore(auto&& value) requires is_same_naked_v<decltype(value), storage_t<T>>
{
	using restore_type = restored_t<T>;
	if constexpr (::std::is_lvalue_reference_v<T> && ::std::same_as<T, restore_type>)
	{
		return static_cast<restore_type>(*value);
	}
	else if constexpr (::std::is_rvalue_reference_v<T> && ::std::same_as<::std::remove_reference_t<T>, restore_type>)
	{
		return static_cast<restore_type>(NGS_PP_PERFECT_FORWARD(value));
	}
	else if constexpr (::std::is_array_v<T> && requires{ requires ::std::same_as<::std::add_pointer_t<::std::ranges::range_value_t<T>>, restore_type>; })
	{
		return static_cast<restore_type>(NGS_PP_PERFECT_FORWARD(value));
	}
	else
	{
		static_assert(::std::convertible_to<decltype(value), restore_type>, "can't restore T");
		return /*static_cast<restore_type>*/NGS_PP_PERFECT_FORWARD(value);
	}
}

NGS_TYPE_TRAIT_END