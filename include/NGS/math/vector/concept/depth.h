#pragma once

#include "../anchor.h"
#include "../depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept generalized_vector = ::std::ranges::random_access_range<_V>;

template<class _V>
concept pure_vector = generalized_vector<_V> && depth_v<_V> == 1;

template<class _V>
concept non_vector = !generalized_vector<_V>;

template<class _T>
concept scalar = non_vector<_T> && (::std::is_scalar_v<type_traits::naked_t<_T>> || cpt::is_specialization_of<type_traits::naked_t<_T>, ::std::complex>);

template<class _V>
concept scalar_vector = pure_vector<_V> && scalar<::std::ranges::range_value_t<_V>>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(pure_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(generalized_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(non_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(scalar);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(scalar_vector);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

template<generalized_vector _V>
struct depth<_V> : ccpt::constant_<depth_t, depth_v<::std::ranges::range_value_t<_V>> +1> {};

NGS_LIB_END