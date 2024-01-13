#pragma once

#include "../extent.h"
#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T> concept dynamic_vector = generalized_vector<_T> && extent_v<_T> == dynamic_extent;
template<class _T> concept adapter_vector = generalized_vector<_T> && extent_v<_T> == adapter_extent;
template<class _T> concept static_extent_vector = generalized_vector<_T> && !dynamic_vector<_T> && !adapter_vector<_T>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(dynamic_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(adapter_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(static_extent_vector);

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

template<class _V, class _With> requires !adapter_vector<_With> || !adapter_vector<_V>
struct static_extent : ccpt::constant_<extent_t, adapter_vector<_V> ? extent_v<_With> : extent_v<_V>> {};
template<class _V, class _With>
constexpr extent_t static_extent_v = static_extent<_V, _With>::value;

NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY_ENV(static_extent);

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

///\brief is same extent between two vectors in compile time
template<class _L, class _R> concept same_extent = (!adapter_vector<_L> || !adapter_vector<_R>) && (static_extent_v<_L, _R> == static_extent_v<_R, _L>);

///\brief is maybe same extent between two vectors in compile time
///\note we don't know is same type or not in compile time when the vector with dynamic extent
template<class _L, class _R> concept maybe_same_extent = same_extent<_L, _R> || (dynamic_vector<_L> || dynamic_vector<_R>);

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_BINARY(same_extent);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_BINARY(maybe_same_extent);

template<class _V, extent_t _Extent>
concept vector_with_extent = static_extent_vector<_V> && extent_v<_V> == _Extent;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_BINARY(vector_with_extent);

NGS_LIB_MODULE_END