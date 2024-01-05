#pragma once

#include "./expression.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

using adapters::vectors::assignable;
using adapters::vectors::callable_contain;
using adapters::vectors::copyable;

template<class _T, class _N = type_traits::naked_t<_T>>
concept container = expression<_T> && assignable<_N, traits::vectors::value_t<_N>>;

template <class _T>
concept output_wrapper = container<_T> && assignable<_T, traits::vectors::value_t<_T>>;

template<class _T>
concept sparse = container<_T> && callable_contain<_T>;

NGS_MATH_LA_VECTOR_CONCEPT_END
NGS_MATH_LA_VECTOR_TRAIT_BEGIN

template<class _T>
struct closure
{
	//copy
	using type = type_traits::object_t<_T>;
	using param_type = type_traits::add_cvref_like_t<const int&, _T>;
};

template<concepts::vectors::container _T>
struct closure<_T>
{
	using cvref_type = _T;
	using naked_type = type_traits::naked_t<_T>;
	using object_type = type_traits::object_t<_T>;
	//if _T is xvalue or prvalue, use copy, otherwise use reference
	using type = std::conditional_t<
		std::is_rvalue_reference_v<cvref_type>,
		naked_type,
		std::add_lvalue_reference_t<object_type>
	>;
	using param_type = std::conditional_t<
		std::is_rvalue_reference_v<cvref_type>,
		std::add_lvalue_reference_t<std::add_const_t<naked_type>>,
		std::add_lvalue_reference_t<object_type>
	>;
};

template<class _T> using closure_t = typename closure<_T>::type;
template<class _T> using closure_param_t = typename closure<_T>::param_type;

NGS_MATH_LA_VECTOR_TRAIT_END