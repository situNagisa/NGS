#pragma once

#include "./transform.h"
#include "../operate.h"
#include "../iterator.h"
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
	using binary_view = transform_view < binary_transformer_t<_Operate>{}, static_extent_v<_L, _R>, packet<_L, _R>, NGS_MATH_VECTOR_OPERATE_NS::size > ;

}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using add_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) + NGS_PP_PERFECT_FORWARD(right); } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using subtract_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) - NGS_PP_PERFECT_FORWARD(right); } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using multiply_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) * NGS_PP_PERFECT_FORWARD(right); } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using divide_value_view = _detail::binary_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) / NGS_PP_PERFECT_FORWARD(right); } > ;

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto add_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return add_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto subtract_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return subtract_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto multiply_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return multiply_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto divide_value(_L&& left, _R&& right)
{
	NGS_MATH_VECTOR_CHECK_SIZE(left, right);
	return divide_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using add_view = add_value_view<_L, _R>;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using subtract_view = subtract_value_view<_L, _R>;

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) add(_L&& left, _R&& right) { return NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) subtract(_L&& left, _R&& right) { return NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }

NGS_LIB_MODULE_END

NGS_LIB_BEGIN

template<operator_vector _L, operator_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_vector _L, operator_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_vector _L, operator_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<operator_vector _L, operator_vector _R> requires maybe_same_extent<_L, _R>
constexpr decltype(auto) operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END