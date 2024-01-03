#pragma once

#include "./transform.h"
#include "../operate.h"
#include "../iterator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{

	template<input_vector _L, input_vector _R, auto _Operate> requires maybe_same_extent<_L, _R>
	using binary_view = transform_view < static_extent<_L, _R>, binary_transformer_t<_Operate>{}, NGS_MATH_VECTOR_OPERATE_NS::size, _L, _R > ;

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
	return add_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto subtract_value(_L&& left, _R&& right)
{
	return subtract_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto multiply_value(_L&& left, _R&& right)
{
	return multiply_value_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto divide_value(_L&& left, _R&& right)
{
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

namespace detail
{
	template<class _L, class _R>
	concept allow_operator_functor =
		tag_vector<_L> && tag_vector<_R> &&
		scalar_vector<_L> && scalar_vector<_R> &&
		maybe_same_extent<_L, _R>;
}

template<input_vector _L, input_vector _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires detail::allow_operator_functor<_L, _R>
constexpr decltype(auto) operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END