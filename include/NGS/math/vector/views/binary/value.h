#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<auto _Operate>
	struct binary_transformer_t
	{
		constexpr decltype(auto) operator()(index_t index, auto&& left, auto&& right)const
		{
			return _Operate(
				NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(left), index),
				NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(right), index)
			);
		}
	};

	template<class _L, class _R, auto _Operate>
	using binary_view = transform_default_sentinel_view < binary_transformer_t<_Operate>{}, static_extent_v<_L, _R>, _L, _R > ;

	template<class _L, class _R>
	concept binary_value_concept =
		accessable_vector<_L> && accessable_vector<_R> &&
		input_vector<_L> && input_vector<_R> &&
		maybe_same_extent<_L, _R>;

	template<class _L, class _R>
	concept binary_value_operatable = binary_value_concept<_L, _R>&& operator_vector<_L>&& operator_vector<_R>;
}

template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
using add_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) + NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
using subtract_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) - NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
using multiply_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) * NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
using divide_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) / NGS_PP_PERFECT_FORWARD(right); } > ;

template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
constexpr auto add_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return add_value_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
constexpr auto subtract_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return subtract_value_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
constexpr auto multiply_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return multiply_value_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_value_concept<_L, _R>
constexpr auto divide_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return divide_value_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}


NGS_LIB_MODULE_END

NGS_MATH_VECTOR_OPERATOR_BEGIN

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
constexpr decltype(auto) operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::add_value_view<_L&, _R&&>>
constexpr decltype(auto) operator+=(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::subtract_value_view<_L&, _R&&>>
constexpr decltype(auto) operator-=(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::multiply_value_view<_L&, _R&&>>
constexpr decltype(auto) operator*=(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::multiply_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_value_operatable<_L, _R>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::divide_value_view<_L&, _R&&>>
constexpr decltype(auto) operator/=(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::divide_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

NGS_MATH_VECTOR_OPERATOR_END