#pragma once

#include "../operate.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t major, index_t minor, auto&& matrix)const
		{
			return NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(matrix), minor, major);
		}
	}transpose_transformer{};
}

template<input_or_output_matrix _M>
using transpose_view = transform_depend_view<_detail::transpose_transformer, _M>;

constexpr decltype(auto) transpose(input_or_output_matrix auto&& matrix)
{
	return transpose_view<decltype(matrix)>(NGS_PP_PERFECT_FORWARD(matrix));
}

NGS_LIB_MODULE_END