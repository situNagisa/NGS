#pragma once

#include "./variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<variables::variable...> struct fields{};

template<class...>
struct make_fields { using type = fields<>; };

template<class First,class... Rest>
struct make_fields<First,Rest...>
{
	using type = type_traits::naked_t<decltype([]
		{
			using first_type = First;

			if constexpr (!sizeof...(Rest)) {
				if constexpr (variables::variable<first_type>) {
					return declval<fields<first_type>>();
				}
				else {
					return declval<fields<meta_variable<first_type>>>();
				}
			}
			else {
				using result_type = fields<
					std::conditional_t<variables::variable<first_type>, first_type, meta_variable<first_type>>,
					std::conditional_t<variables::variable<Rest>, Rest, meta_variable<Rest>>...
				>;
				return declval<result_type>();
			}
		}())>;
};

template<class... Ts>
using make_fields_t = typename make_fields<Ts...>::type;

NGS_LIB_MODULE_END