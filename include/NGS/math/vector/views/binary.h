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
	struct binary_view : basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<binary_view<_L, _R, _Operate>>
	{
		NGS_MPL_ENVIRON_BEGIN(binary_view);
	public:
		using left_trait = param_trait<_L>;
		using right_trait = param_trait<_R>;

		constexpr static auto operate = _Operate;
		constexpr static auto extent = static_extent<_L, _R>;

		constexpr static auto dereference(index_t index, typename left_trait::const_pointer left, typename right_trait::const_pointer right)
		{
			return operate(NGS_LIB_NAME::random_access(*left, index), NGS_LIB_NAME::random_access(*right, index));
		}

		using value_type = decltype(dereference(0, nullptr, nullptr));
		using iterator = vector_iterator<value_type, dereference, typename left_trait::const_pointer, typename right_trait::const_pointer>;

		constexpr binary_view(typename left_trait::param left, typename right_trait::param right)
			: _left(&left)
			, _right(&right)
		{
			NGS_MATH_VECTOR_CHECK_SIZE(*_left, *_right);
		}

		constexpr auto begin()const { return iterator(0, _left, _right); }
		constexpr auto end()const { return iterator(NGS_LIB_NAME::size(*_left, *_right), _left, _right); }

		NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

	public:
		typename left_trait::const_pointer _left;
		typename right_trait::const_pointer _right;
	};
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