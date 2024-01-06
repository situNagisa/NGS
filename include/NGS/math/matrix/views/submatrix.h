#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct rectangle
	{
		index_t x = 0;
		index_t y = 0;
		extent_t width = dynamic_extent;
		extent_t height = dynamic_extent;
	};

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t major, index_t minor, auto&& matrix, const rectangle& rect) const noexcept
		{
			return NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(matrix), major + rect.x, minor + rect.y);
		}
	}submatrix_transformer{};
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(auto&& matrix, const rectangle& rect) const noexcept
		{
			return rect.width;
		}
	}submatrix_major_sentinel{};
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(auto&& matrix, const rectangle& rect) const noexcept
		{
			return rect.height;
		}
	}submatrix_minor_sentinel{};
}

template<generalized_matrix _M>
using submatrix_view = transform_view<_detail::submatrix_transformer, dynamic_extent, dynamic_extent, _detail::submatrix_major_sentinel, _detail::submatrix_minor_sentinel, _M, _detail::rectangle>;

constexpr auto submatrix(generalized_matrix auto&& matrix, const _detail::rectangle& range)
{
	return submatrix_view<decltype(matrix)>(NGS_PP_PERFECT_FORWARD(matrix), range);
}

NGS_LIB_MODULE_END