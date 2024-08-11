#pragma once

#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class... Tuples>
	using tuple_cat_t = ::std::remove_cvref_t<decltype(::std::tuple_cat(::std::declval<Tuples>()...))>;

	template<class>
	struct flatten;

	template<class T>
	using flatten_t = typename flatten<::std::remove_cvref_t<T>>::type;

	template<template<class...>class Template, class First, class... Rest>
	struct flatten<Template<First, Rest...>>
	{
		constexpr static decltype(auto) apply()
		{
			using first_type = First;

			// flatten meta structure
			if constexpr (structure<first_type>) {

				using first_flattened_type = flatten_t<field_seq_t<first_type>>;
				if constexpr (!sizeof...(Rest))
				{
					return ::std::type_identity<first_flattened_type>{};
				}
				else
				{
					using rest_type = flatten_t<::std::tuple<Rest...>>;
					return ::std::type_identity<tuple_cat_t<first_flattened_type, rest_type>>{};
				}
			}
			else
			{
				using first_flattened_type = ::std::tuple<first_type>;
				if constexpr (!sizeof...(Rest))
				{
					return ::std::type_identity<first_flattened_type>{};
				}
				else
				{
					using rest_type = flatten_t<::std::tuple<Rest...>>;
					return ::std::type_identity<tuple_cat_t<first_flattened_type, rest_type>>{};
				}
			}
		}

		using type = typename ::std::remove_cvref_t<decltype(apply())>::type;
	};
}

namespace _detail2
{
	template<class... Tuples>
	using tuple_cat_t = ::std::remove_cvref_t<decltype(::std::tuple_cat(::std::declval<Tuples>()...))>;

	template<class>
	struct flatten;

	template<class T>
	using flatten_t = typename flatten<::std::remove_cvref_t<T>>::type;

	template<template<class...>class Template, class First, class... Rest>
	struct flatten<Template<First, Rest...>>
	{
		using type = tuple_cat_t<::std::tuple<First>, flatten_t<::std::tuple<Rest...>>>;
	};
	template<template<class...>class Template, class First>
	struct flatten<Template<First>>
	{
		using type = tuple_cat_t<::std::tuple<First>>;
	};
	template<template<class...>class Template, structure First, class... Rest>
	struct flatten<Template<First, Rest...>>
	{
		using type = tuple_cat_t<flatten_t<field_seq_t<First>>, flatten_t<::std::tuple<Rest...>>>;
	};
	template<template<class...>class Template, structure First>
	struct flatten<Template<First>>
	{
		using type = tuple_cat_t<flatten_t<field_seq_t<First>>>;
	};
}

template<fields::field T>
struct flatten { using type = ::std::tuple<T>; };

template<structure T>
struct flatten<T>
{
	using type = _detail2::flatten_t<field_seq_t<T>>;
};

template<fields::field Struct>
using flatten_t = typename flatten<Struct>::type;



namespace _detail
{
	template<class>
	struct is_flattened_struct : ::std::false_type {};

	template<template<class...>class Template, class... Fields>
	struct is_flattened_struct<Template<Fields...>> : ::std::bool_constant<(pure_field<Fields> && ...)> {};

}

/**
 * @brief 判断结构体是否已经展开
 *
 * @tparam T 待判断的结构体
 */
template<class T>
concept flattened_structure = structure<T> && _detail::is_flattened_struct<::std::remove_cvref_t<field_seq_t<T>>>::value;



NGS_LIB_MODULE_END