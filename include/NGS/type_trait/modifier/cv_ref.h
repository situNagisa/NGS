#pragma once

#include "./cv.h"
#include "./reference.h"

NGS_TYPE_TRAIT_BEGIN

template<class _CVR, class _T>
struct add_cvref_like
{
	using type = add_reference_like_t<_CVR, add_cv_like_t<std::remove_reference_t<_CVR>, std::remove_reference_t<_T>>>;
};
template<class _CVR, class _T>
using add_cvref_like_t = typename add_cvref_like<_CVR, _T>::type;

NGS_TYPE_TRAIT_END

#if defined(__cpp_lib_forward_like)
#define NGS_PP_PERFECT_FORWARD_LIKE(target,like) std::forward_like<NGS_PP_EXPRESSION_TYPE(like)>(target)
#else
#	define NGS_PP_PERFECT_FORWARD_LIKE(target,like) std::forward<NGS_ type_traits::add_cvref_like_t<decltype(like),decltype(target)>>(target)
#endif