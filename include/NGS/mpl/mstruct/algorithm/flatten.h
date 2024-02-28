#pragma once

#include "../variable.h"
#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class Fields>
	struct flatten {};

	template<template<class...>class Template,class First, class... Rest>
	struct flatten<Template<First, Rest...>> {
		constexpr static auto _get() {
			using first_type = First;
			using first_value_type = variables::variable_value_t<first_type>;

			// flatten meta structure
			if constexpr (basic::structure<first_value_type>) {

				using first_flattened_type = typename flatten<basic::fields_t<first_value_type>>::type;
				if constexpr (!sizeof...(Rest))
				{
					return ::ngs::declval<first_flattened_type>();
				}
				else
				{
					using rest_type = typename flatten<Template<Rest...>>::type;
					return ::ngs::declval<external::nboost::fusion::result_of::cat_t<Template,first_flattened_type, rest_type>>();
				}

			}
			else
			{
				using first_flattened_type = Template<first_type>;
				if constexpr (!sizeof...(Rest))
				{
					return ::ngs::declval<first_flattened_type>();
				}
				else
				{
					using rest_type = typename flatten<Template<Rest...>>::type;
					return ::ngs::declval<external::nboost::fusion::result_of::cat_t<Template, first_flattened_type, rest_type>>();
				}
			}
		}
		using type = type_traits::naked_t<decltype(_get())>;
	};
}

template<basic::structure Struct>
struct flatten_as_sequence { using type = typename _detail::flatten<basic::fields_t<Struct>>::type; };

template<basic::structure Struct>
using flatten_as_sequence_t = typename flatten_as_sequence<Struct>::type;

template<class>
struct flatten{};

template<class Struct>
using flatten_t = typename flatten<Struct>::type;

namespace _detail
{
	template<class>
	struct is_flattened_struct : ::std::false_type {};

	template<template<class...>class Template, class... Fields>
	struct is_flattened_struct<Template<Fields...>> : ::std::bool_constant<!(basic::structure<variables::variable_value_t<Fields>> || ...)> {};

}

/**
 * @brief 判断结构体是否已经展开
 *
 * @tparam _Struct 待判断的结构体
 */
template<class T>
concept flattened_structure = basic::structure<T> && _detail::is_flattened_struct<basic::fields_t<T>>::value;


NGS_LIB_MODULE_END