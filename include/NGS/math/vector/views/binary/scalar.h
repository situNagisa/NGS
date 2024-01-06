#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<auto _Operate>
	struct binary_scalar_transformer_t
	{
		constexpr decltype(auto) operator()(index_t index, auto&& left, auto&& right)const
		{
			constexpr bool left_is_vector = input_or_output_vector<decltype(left)>;
			constexpr bool left_is_scalar = scalar<decltype(left)>;
			constexpr bool right_is_vector = input_or_output_vector<decltype(right)>;
			constexpr bool right_is_scalar = scalar<decltype(right)>;

			static_assert((left_is_scalar && right_is_vector) || (left_is_vector && right_is_scalar));

			if constexpr (left_is_scalar && right_is_vector)
			{
				return _Operate(
					NGS_PP_PERFECT_FORWARD(left),
					NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(right), index)
				);
			}
			else if constexpr (left_is_vector && right_is_scalar)
			{
				return _Operate(
					NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(left), index),
					NGS_PP_PERFECT_FORWARD(right)
				);
			}
		}
	};

	template<class _L, class _R, auto _Operate>
	using binary_scalar_view = transform_default_sentinel_view < binary_scalar_transformer_t<_Operate>{}, input_or_output_vector<_L> ? extent_v<_L> : extent_v<_R>, _L, _R > ;

	template<class _V, class _With, template<class...>class _Predicate>
	concept half_binary_scalar_concept = scalar<_With> && input_vector<_V> && accessable_vector<_V> && _Predicate<::std::ranges::range_value_t<_V>, _With>::value;

	template<class _L, class _R, template<class...>class _Predicate>
	concept binary_scalar_concept = half_binary_scalar_concept<_L, _R, _Predicate> || half_binary_scalar_concept<_R, _L, _Predicate>;

	template<class _V, class _With>
	concept half_binary_scalar_operatable = operator_vector<_V>;

	template<class _L, class _R, template<class...>class _Predicate>
	concept binary_scalar_operatable = binary_scalar_concept<_L, _R, _Predicate> && (half_binary_scalar_operatable<_L, _R> || half_binary_scalar_operatable<_R, _L>);
}

template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_addable>
using add_scalar_view = _detail::binary_scalar_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) + NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_subtractable>
using subtract_scalar_view = _detail::binary_scalar_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) - NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_multipliable>
using multiply_scalar_view = _detail::binary_scalar_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) * NGS_PP_PERFECT_FORWARD(right); } > ;
template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_divisible>
using divide_scalar_view = _detail::binary_scalar_view < _L, _R, [](auto&& left, auto&& right) {return NGS_PP_PERFECT_FORWARD(left) / NGS_PP_PERFECT_FORWARD(right); } > ;

template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_addable>
constexpr auto add_scalar(_L&& left, _R&& right)
{
	return add_scalar_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_subtractable>
constexpr auto subtract_scalar(_L&& left, _R&& right)
{
	return subtract_scalar_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_multipliable>
constexpr auto multiply_scalar(_L&& left, _R&& right)
{
	return multiply_scalar_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

template<class _L, class _R> requires _detail::binary_scalar_concept<_L, _R, type_traits::operators::is_divisible>
constexpr auto divide_scalar(_L&& left, _R&& right)
{
	return divide_scalar_view<_L&&, _R&&>{NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)};
}

NGS_LIB_MODULE_END

NGS_MATH_VECTOR_OPERATOR_BEGIN

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_addable>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_subtractable>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_multipliable>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_divisible>
constexpr decltype(auto) operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_addable>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::add_scalar_view<_L&, _R&&>>
constexpr decltype(auto) operator+=(_L& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::add_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_subtractable>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::subtract_scalar_view<_L&, _R&&>>
constexpr decltype(auto) operator-=(_L& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::subtract_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_multipliable>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::multiply_scalar_view<_L&, _R&&>>
constexpr decltype(auto) operator*=(_L& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::multiply_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

template<class _L, class _R>
	requires NGS_LIB_MODULE_NAME::_detail::binary_scalar_operatable<_L, _R, type_traits::operators::is_divisible>
&& assignable_from<_L&, NGS_LIB_MODULE_NAME::divide_scalar_view<_L&, _R&&>>
constexpr decltype(auto) operator/=(_L& left, _R&& right)
{
	NGS_MATH_VECTOR_OPERATE_NS::assign(left, NGS_LIB_MODULE_NAME::divide_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)));
	return left;
}

NGS_MATH_VECTOR_OPERATOR_END