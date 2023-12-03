#pragma once

#include "./structure.h"

NGS_LIB_MODULE_BEGIN

NGS_MPL_FUNCTION(flatten, class...);

/**
 * @brief 将输入的参数展开成`非元结构体`序列
 *
 * @tparam 元变量...
 * @tparam CAny...
 * @tparam boost::fusion::vector,CAny 递归展开序列
 *
 * @return 展开后的`非元结构体`序列
 */
template<class... _Types>
using flatten_t = typename flatten<_Types...>::result_type;

NGS_MPL_FUNCTION(flatten, class _First, class... _Rest) < boost::fusion::vector<_First, _Rest...> > {
private:
	constexpr static auto _GET_RESULT_TYPE() {
		// make _First as variable
		using variable_type = variable<_First>;
		// get _First type in storage(decay type)
		// the type will be solved in this layer
		using type = typename variable_type::storage_type;

		constexpr size_t rest_count = sizeof...(_Rest);

		// flatten meta structure
		if constexpr (CStructureDescribe<type>) {
			using first_flattened_type = type_traits::naked_t<flatten_t<typename type::variable_types>>;
			if constexpr (!rest_count)
			{
				return ::ngs::declval<first_flattened_type>();
			}
			else
			{
				using rest_type = flatten_t<boost::fusion::vector<_Rest...>>;
				return ::ngs::declval<nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
			}
		}
		else
		{
			using first_flattened_type = boost::fusion::vector<variable_type>;
			if constexpr (!rest_count)
			{
				return ngs::declval<first_flattened_type>();
			}
			else
			{
				using rest_type = flatten_t<boost::fusion::vector<_Rest...>>;
				return declval<nboost::fusion::result_of::cat_t<first_flattened_type, rest_type>>();
			}
		}
	}
public:
	NGS_MPL_TYPE result_type = type_traits::naked_t<decltype(_GET_RESULT_TYPE())>;
};

NGS_MPL_FUNCTION(flatten, CVariable... _Variables) < _Variables... > {
	using result_type = flatten_t<boost::fusion::vector<_Variables...>>;
};

NGS_MPL_FUNCTION(flatten, class... _Types) < _Types... > {
	using result_type = flatten_t<boost::fusion::vector<variable<_Types>...>>;
};


NGS_MPL_FUNCTION(flatten_as_struct, CStructureDescribe _Struct, class = flatten_t<_Struct>);
NGS_MPL_FUNCTION(flatten_as_struct, CStructureDescribe _Struct, template<class...>class _Sequence, CVariable... _Variables) < _Struct, _Sequence<_Variables...> > {
	using align_type = ccpt::uint_<_Struct::align>;
	using result_type = structure<align_type, _Variables...>;
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
