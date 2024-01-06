#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept left_multiply_vector = pure_matrix<_L> && vectors::pure_vector<_R> && vectors::maybe_same_extent<::std::ranges::range_value_t<_L>, _R>;

	template<class _L, class _R>
	concept right_multiply_vector = vectors::pure_vector<_L> && pure_matrix<_R> && vectors::maybe_same_extent<_L, _R>;

	template<class _L, class _R>
	concept multiply_vector = left_multiply_vector<_L, _R> || right_multiply_vector<_L, _R>;

	template<class _M, class _V>
	concept half_multiply_vector_operatable = operator_matrix<_M> && vectors::operator_vector<_V>;

	template<class _L, class _R>
	concept multiply_vector_operatable = multiply_vector<_L, _R> && (half_multiply_vector_operatable<_L, _R> || half_multiply_vector_operatable<_R, _L>);

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t index, auto&& left, auto&& right)const
		{
			if constexpr (vectors::pure_vector<decltype(left)> && pure_matrix<decltype(right)>)
			{
				return vectors::ops::product_inner(NGS_PP_PERFECT_FORWARD(left), NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::minor(right, index));
			}
			else if constexpr (pure_matrix<decltype(left)> && vectors::pure_vector<decltype(right)>)
			{
				return vectors::ops::product_inner(NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::major(left, index), NGS_PP_PERFECT_FORWARD(right));
			}
			else
			{
				static_assert(cpt::none<decltype(left)>, "invalid type");
			}
		}
	}multiply_vector_transformer{};

	template<extent_t _Extent>
	struct left_multiply_minor_sentinel_t
	{
		constexpr decltype(auto) operator()(auto&& left, auto&& right)const
		{
			return NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<_Extent>()(NGS_PP_PERFECT_FORWARD(right), NGS_PP_PERFECT_FORWARD(left));
		}
	};
	template<extent_t _Extent>
	inline constexpr left_multiply_minor_sentinel_t<_Extent> left_multiply_minor_sentinel{};

	template<extent_t _L, extent_t _R>
		requires (_L != adapter_extent || _R != adapter_extent)
	inline constexpr extent_t multiply_extent = _L == adapter_extent ? _R : _L;

	template<class _L, class _R> requires left_multiply_vector<_L, _R>
	using left_multiply_vector_view = vectors::views::transform_default_sentinel_view<
		multiply_vector_transformer,
		static_extent_v<_L, _R>,
		_L, _R
	>;

	template<class _L, class _R> requires right_multiply_vector<_L, _R>
	using right_multiply_vector_view = vectors::views::transform_default_sentinel_view <
		multiply_vector_transformer,
		static_extent_v<_L, ::std::ranges::range_value_t<_R>>,
		_L, _R>;

	template<class _L, class _R> requires multiply_vector<_L, _R>
	struct multiply_vector_view {};

	template<class _L, class _R> requires left_multiply_vector<_L, _R>
	struct multiply_vector_view<_L, _R>
	{
		using type = left_multiply_vector_view<_L, _R>;
	};

	template<class _L, class _R> requires right_multiply_vector<_L, _R>
	struct multiply_vector_view<_L, _R>
	{
		using type = right_multiply_vector_view<_L, _R>;
	};
}

template<class _L, class _R> requires _detail::multiply_vector<_L, _R>
using multiply_vector_view = typename _detail::multiply_vector_view<_L, _R>::type;

template<class _L, class _R> requires _detail::multiply_vector<_L, _R>
constexpr auto multiply_vector(_L&& left, _R&& right)
{
	//NGS_MATH_VECTOR_CHECK_SIZE(vectors::ops::access(NGS_PP_PERFECT_FORWARD(left), 0), right);
	return multiply_vector_view<_L&&, _R&&>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_MODULE_END

NGS_MATH_MATRIX_OPERATOR_BEGIN

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::multiply_vector_operatable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_vector(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_MATRIX_OPERATOR_END