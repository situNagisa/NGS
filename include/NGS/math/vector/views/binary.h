#pragma once

#include "../param_trait.h"
#include "../size.h"
#include "../iterator.h"
#include "../access.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<input_vector _L, input_vector _R, auto _Operate> requires maybe_same_extent<_L, _R>
	struct binary_view : basic_vector
	{
		NGS_MPL_ENVIRON_BEGIN(binary_view);
	public:
		using left_trait = param_trait<_L>;
		using right_trait = param_trait<_R>;

		constexpr static auto operate = _Operate;
		constexpr static auto extent = static_extent<_L, _R>;
		using value_type = type_traits::naked_t<::std::invoke_result_t<decltype(operate), ::std::ranges::range_value_t<_L>, ::std::ranges::range_value_t<_R>>>;


		constexpr binary_view(typename left_trait::param left, typename right_trait::param right)
			: _left(NGS_PP_PERFECT_FORWARD(left))
			, _right(NGS_PP_PERFECT_FORWARD(right))
		{
			NGS_MATH_VECTOR_CHECK_SIZE(_left, _right);
		}

		constexpr static auto dereference(index_t index, typename left_trait::const_pointer left, typename right_trait::const_pointer right)
		{
			return operate(NGS_LIB_NAME::random_access(*left, index), NGS_LIB_NAME::random_access(*right, index));
		}
		using iterator = vector_iterator<const value_type, dereference, typename left_trait::const_pointer, typename right_trait::const_pointer>;

		constexpr auto begin()const { return iterator(0, &_left, &_right); }
		constexpr auto end()const { return iterator(NGS_LIB_NAME::size(_left, _right), &_left, &_right); }

		NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

	public:
		typename left_trait::decay _left;
		typename right_trait::decay _right;
	};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using add_view = _detail::binary_view < _L, _R, [](::std::ranges::range_value_t<_L> left, ::std::ranges::range_value_t<_R> right) {return left + right; } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using subtract_view = _detail::binary_view < _L, _R, [](::std::ranges::range_value_t<_L> left, ::std::ranges::range_value_t<_R> right) {return left - right; } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using multiply_view = _detail::binary_view < _L, _R, [](::std::ranges::range_value_t<_L> left, ::std::ranges::range_value_t<_R> right) {return left * right; } > ;
template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
using divide_view = _detail::binary_view < _L, _R, [](::std::ranges::range_value_t<_L> left, ::std::ranges::range_value_t<_R> right) {return left / right; } > ;

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto add(_L&& left, _R&& right)
{
	return add_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto subtract(_L&& left, _R&& right)
{
	return subtract_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto multiply(_L&& left, _R&& right)
{
	return multiply_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto divide(_L&& left, _R&& right)
{
	return divide_view<_L, _R>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

NGS_LIB_MODULE_END

NGS_LIB_BEGIN

template<input_vector _L, input_vector _R> requires tag_vector<_L>&& tag_vector<_R>&& maybe_same_extent<_L, _R>
constexpr auto operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires tag_vector<_L>&& tag_vector<_R>&& maybe_same_extent<_L, _R>
constexpr auto operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires tag_vector<_L>&& tag_vector<_R>&& maybe_same_extent<_L, _R>
constexpr auto operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<input_vector _L, input_vector _R> requires maybe_same_extent<_L, _R>
constexpr auto operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_LIB_END