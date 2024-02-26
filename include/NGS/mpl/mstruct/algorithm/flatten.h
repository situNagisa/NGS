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
					using rest_type = flatten_t<::boost::fusion::vector<Rest...>>;
					return ::ngs::declval<external::nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
				}

			}
			else
			{
				using first_flattened_type = ::boost::fusion::vector<variable_type>;
				if constexpr (!sizeof...(Rest))
				{
					return ::ngs::declval<first_flattened_type>();
				}
				else
				{
					using rest_type = flatten_t<::boost::fusion::vector<Rest...>>;
					return declval<external::nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
				}
			}
		}
		using type = type_traits::naked_t<decltype(_get())>;
	};


	template<variables::variable... Fields>
	struct  flatten < Fields... > {
		using type = flatten_t<boost::fusion::vector<Fields...>>;
	};

	template<class... Ts>
	struct  flatten < Ts... > {
		using type = flatten_t<boost::fusion::vector<variables::meta_variable<Ts>...>>;
	};
}

/**
 * @brief 将输入的参数展开成`非元结构体`序列
 *
 * @tparam 元变量...
 * @tparam CAny...
 * @tparam boost::fusion::vector,CAny 递归展开序列
 *
 * @return 展开后的`非元结构体`序列
 */
template<class... Ts>
using flatten_t = typename flatten<Ts...>::type;

template<class First, class... Rest>
struct flatten< ::boost::fusion::vector<First, Rest...> > {
private:
	constexpr static auto _get() {
		// make _First as variable
		using variable_type = variables::meta_variable<First>;
		// get _First type in storage(decay type)
		// the type will be solved in this layer
		using type = variables::variable_value_t<variable_type>;

		constexpr size_t rest_count = sizeof...(Rest);

		// flatten meta structure
		if constexpr (basic::structure<type>) {
			using first_flattened_type = type_traits::naked_t<flatten_t<basic::fields_t<type>>>;
			if constexpr (!rest_count)
			{
				return ::ngs::declval<first_flattened_type>();
			}
			else
			{
				using rest_type = flatten_t<::boost::fusion::vector<Rest...>>;
				return ::ngs::declval<external::nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
			}
		}
		else
		{
			using first_flattened_type = ::boost::fusion::vector<variable_type>;
			if constexpr (!rest_count)
			{
				return ::ngs::declval<first_flattened_type>();
			}
			else
			{
				using rest_type = flatten_t<::boost::fusion::vector<Rest...>>;
				return declval<external::nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
			}
		}
	}
public:
	NGS_MPL_TYPE type = type_traits::naked_t<decltype(_get())>;
};

NGS_MPL_FUNCTION(flatten, variables::variable... Fields) < Fields... > {
	using type = flatten_t<boost::fusion::vector<Fields...>>;
};

NGS_MPL_FUNCTION(flatten, class... Ts) < Ts... > {
	using type = flatten_t<boost::fusion::vector<variables::meta_variable<Ts>...>>;
};


NGS_MPL_FUNCTION(flatten_as_struct, basic::structure Struct, class = flatten_t<Struct>);
NGS_MPL_FUNCTION(flatten_as_struct, basic::structure Struct, template<class...>class Sequence, variables::variable... Fields) < Struct, Sequence<Fields...> > {
	using type = structure<typename Struct::align_type, Fields...>;
};

/**
 * @brief 将结构体的`元变量`展开直至所有元变量都为基础变量
 *
 * @tparam _Struct `元结构体`
 *
 * @return 展开后的元结构体
 */
template<CStructureDescribe _Struct>
using flatten_as_struct_t = typename flatten_as_struct<_Struct>::result_type;

namespace detail
{
	template<class>
	struct is_flattened_struct : std::false_type {};

	template<template<class...>class _Template, CVariable... _Variables>
	struct is_flattened_struct<_Template<_Variables...>> : std::bool_constant<!(CStructure<typename _Variables::original_type> || ...)> {};

}

/**
 * @brief 判断结构体是否已经展开
 *
 * @tparam _Struct 待判断的结构体
 */
template<class _Struct>
concept CFlattenedStructure = CStructure<_Struct> && detail::is_flattened_struct<typename _Struct::variable_types>::value;


NGS_LIB_MODULE_END