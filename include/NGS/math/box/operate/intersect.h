#pragma once

#include "../concept.h"
#include "../container.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr bool is_intersect(box auto&& left, box auto&& right) requires vectors::similar_vector<decltype(left), decltype(right)>
{
	using left_type = decltype(left);
	using right_type = decltype(right);
	constexpr auto extent = vectors::extent_v<left_type>;

	size_t i = 0;

	for (auto&& inter : left)
	{
		if (!inter.is_intersect(vectors::ops::access(NGS_PP_PERFECT_FORWARD(right), i)))
			return false;
		i++;
	}

	return true;
}

namespace _detail
{
	constexpr void intersect(box auto&& left, box auto&& right, box auto& result)
	{
		size_t i = 0;

		for (auto&& inter : left)
		{
			vectors::ops::access(result, i) = inter.intersect(vectors::ops::access(NGS_PP_PERFECT_FORWARD(right), i));
			i++;
		}
	}
}

constexpr auto intersect(box auto&& left, box auto&& right) requires vectors::similar_vector<decltype(left), decltype(right)>
{
	using left_type = decltype(left);
	using right_type = decltype(right);
	using value_type = ::std::common_reference_t<typename vectors::value_t<left_type>::value_type, typename vectors::value_t<right_type>::value_type>;
	constexpr auto extent = vectors::extent_v<left_type>;
	using result_type = NGS_MATH_BOX_CONTAINER_NS::internals<value_type, extent>;

	result_type result{};

	_detail::intersect(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right), result);

	return result;
}

NGS_LIB_MODULE_END
NGS_MATH_BOX_OPERATOR_BEGIN

constexpr auto operator&(box auto&& left, box auto&& right) requires vectors::similar_vector<decltype(left), decltype(right)>
{
	return NGS_LIB_MODULE_NAME::intersect(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr auto operator&=(box auto& left, box auto&& right) requires vectors::similar_vector<decltype(left), decltype(right)>
{
	NGS_LIB_MODULE_NAME::_detail::intersect(left, NGS_PP_PERFECT_FORWARD(right), left);
	return left;
}

NGS_MATH_BOX_OPERATOR_END
