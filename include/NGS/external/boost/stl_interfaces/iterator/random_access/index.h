#pragma once

#include "./iterator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr auto random_access_index_subtract = [](auto&& left, auto&& right) {return ::std::get<0>(NGS_PP_PERFECT_FORWARD(left)) - ::std::get<0>(NGS_PP_PERFECT_FORWARD(right)); };
	inline constexpr auto random_access_index_plus_assign = [](auto& args, auto n) { ::std::get<0>(args) += n; };

	inline constexpr auto random_access_range_index_subtract = [](auto&& left,auto&& right) { return ::std::get<1>(NGS_PP_PERFECT_FORWARD(left)) - ::std::get<1>(NGS_PP_PERFECT_FORWARD(right)); };
	inline constexpr auto random_access_range_index_plus_assign = [](auto& args, auto n) { ::std::get<1>(args) += n; };
}

template<class Value, auto Dereference, class... Args>
using index_random_access_iterator = random_access_iterator<Value, Dereference, _detail::random_access_index_subtract, _detail::random_access_index_plus_assign, ::std::int64_t, Args...>;

template<class Range, class Index, auto Dereference> requires ::std::invocable<decltype(Dereference), Range, Index>
using range_index_random_access_iterator = random_access_iterator <
	::std::invoke_result_t<decltype(Dereference), Range, Index>,
	Dereference, _detail::random_access_range_index_subtract, _detail::random_access_range_index_plus_assign,Range,Index
>;

NGS_LIB_MODULE_END
