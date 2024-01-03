#pragma once

#include "./index.h"
#include "./depth.h"
#include "./value.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail {

	template<template<class...>class _API, index_t _Index, class... _V>
		requires ((_Index < depth_v<_V>) && ...)
	struct anchor { using type = _API<value_t<_V, _Index>...>; };

	template<template<class...>class _API, index_t _Index, class... _V>
	using anchor_t = typename anchor<_API, _Index, _V...>::type;

}

NGS_LIB_END

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY(api)										\
template<class _V, NGS_NS::NGS_LIB_NAME::index_t _Index>								\
struct api##_at : NGS_NS::NGS_LIB_NAME::detail::anchor_t<api, _Index, _V>{}\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY_VALUE(api)				\
template<class _V, NGS_NS::NGS_LIB_NAME::index_t _Index>			\
inline constexpr auto api##_at##_v = api##_at<_V, _Index>::value	\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY_ENV(api)	\
NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY(api);				\
NGS_MATH_VECTOR_RECURSE_ANCHOR_UNARY_VALUE(api)			\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY(api)												\
template<class _V,class _With, NGS_NS::NGS_LIB_NAME::index_t _Index>							\
struct api##_at : NGS_NS::NGS_LIB_NAME::detail::anchor_t<api, _Index, _V, _With>{}	\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY_VALUE(api)					\
template<class _V,class _With, NGS_NS::NGS_LIB_NAME::index_t _Index>		\
inline constexpr auto api##_at##_v = api##_at<_V, _With, _Index>::value		\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY_ENV(api)	\
NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY(api);				\
NGS_MATH_VECTOR_RECURSE_ANCHOR_BINARY_VALUE(api)		\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(api)								\
template<class _V, NGS_NS::NGS_LIB_NAME::index_t _Index>								\
concept api##_at = NGS_NS::NGS_LIB_NAME::api<NGS_NS::NGS_LIB_NAME::value_t<_V, _Index>>	\
//

#define NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_BINARY(api)				\
template<class _V,class _With, NGS_NS::NGS_LIB_NAME::index_t _Index>	\
concept api##_at = NGS_NS::NGS_LIB_NAME::api<							\
	NGS_NS::NGS_LIB_NAME::value_t<_V, _Index>,							\
	NGS_NS::NGS_LIB_NAME::value_t<_With, _Index>>						\
//
