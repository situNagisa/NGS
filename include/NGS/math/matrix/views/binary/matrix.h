#pragma once

#include "./defined.h"

NGS_LIB_BEGIN
namespace NGS_MATH_MATRIX_CPT_NS
{
	template<class _L, class _R>
	concept matrix_multipiable =
		input_matrix<_L> && input_matrix<_R> &&
		vectors::maybe_same_extent<::std::ranges::range_value_t<_L>, _R>;
}

template<class _L, class _R>
struct matrix_multiply_policy {};

template<class _L, class _R>
inline constexpr matrix_multiply_policy<_L, _R> matrix_multiply_policy_v{};

template<class _L, class _R> requires matrix_multipiable<_L, _R>
struct matrix_multiply_policy<_L, _R>
{
	constexpr decltype(auto) operator()(index_t major, index_t minor, auto&& left, auto&& right)const
	{
		using namespace NGS_MATH_MATRIX_TAG_NS;
		using left_matrix_type = decltype(left);
		using left_tag = trait_t<left_matrix_type>;
		using right_matrix_type = decltype(right);
		using right_tag = trait_t<right_matrix_type>;

		if constexpr (::std::derived_from<left_tag, zero> || ::std::derived_from<right_tag, zero>)
		{
			return 0;
		}
		else if constexpr (::std::derived_from<left_tag, identity>)
		{
			return NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(right), major, minor);
		}
		else if constexpr (::std::derived_from<right_tag, identity>)
		{
			return NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(left), major, minor);
		}
		else if constexpr (::std::derived_from<left_tag, diagonal>)
		{
			return
				NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(left), major, major) *
				NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(right), major, minor)
				;
		}
		else if constexpr (::std::derived_from<right_tag, diagonal>)
		{
			return
				NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(left), major, minor) *
				NGS_MATH_MATRIX_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(right), minor, minor)
				;
		}
		else
		{
			return vectors::ops::product_inner(NGS_MATH_MATRIX_OPERATE_NS::major(left, major), NGS_MATH_MATRIX_OPERATE_NS::minor(right, minor));
		}
	}
};

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<extent_t _Extent>
	struct multiply_minor_sentinel_t
	{
		constexpr decltype(auto) operator()(auto&& left, auto&& right)const
		{
			return NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<_Extent>()(NGS_PP_PERFECT_FORWARD(right), NGS_PP_PERFECT_FORWARD(left));
		}
	};
	template<extent_t _Extent>
	inline constexpr multiply_minor_sentinel_t<_Extent> multiply_minor_sentinel{};

	template<class _L, class _R> requires matrix_multipiable<_L, _R>
	using multiply_view = transform_view<
		matrix_multiply_policy_v<_L, _R>,
		major_static_extent_v<_L, _R>, minor_static_extent_v<_R, _L>,
		NGS_MATH_MATRIX_OPERATE_NS::default_major_sentinel<major_static_extent_v<_L, _R>>(),
		multiply_minor_sentinel<minor_static_extent_v<_R, _L>>,
		//functional::binders::bind(
		//	NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<minor_extent_v<_R>>(),
		//	functional::parameter_packet::placeholders::_2,
		//	functional::parameter_packet::placeholders::_1),
		_L, _R>;

	template<class _L, class _R>
	using basic_add_view = vectors::views::add_view<_L, _R>;


}

using _detail::multiply_view;
using vectors::views::add_view;
using vectors::views::subtract_view;

using vectors::views::add;
using vectors::views::subtract;

template<class _L, class _R> requires matrix_multipiable<_L, _R>
constexpr auto multiply(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(vectors::ops::access(NGS_PP_PERFECT_FORWARD(left), 0), right);
	return multiply_view<_L&&, _R&&>(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_MODULE_END

NGS_MATH_MATRIX_OPERATOR_BEGIN

template<operator_matrix _L, operator_matrix _R> requires maybe_same_type<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_matrix _L, operator_matrix _R> requires maybe_same_type<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_matrix _L, operator_matrix _R> requires matrix_multipiable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_MATRIX_OPERATOR_END