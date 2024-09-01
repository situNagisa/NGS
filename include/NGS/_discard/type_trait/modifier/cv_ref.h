#pragma once

#include "./cv.h"
#include "./reference.h"

NGS_TYPE_TRAIT_BEGIN

template<class CVR, class T>
struct add_cvref_like
{
	using type = add_reference_like_t<CVR, add_cv_like_t<std::remove_reference_t<CVR>, std::remove_reference_t<T>>>;
};
template<class CVR, class T>
using add_cvref_like_t = typename add_cvref_like<CVR, T>::type;

NGS_TYPE_TRAIT_END

#if defined(__cpp_lib_forward_like)
#define NGS_PP_PERFECT_FORWARD_LIKE(target,like) std::forward_like<NGS_PP_EXPRESSION_TYPE(like)>(target)
#else
#	define NGS_PP_PERFECT_FORWARD_LIKE(target,like) std::forward<NGS_ type_traits::add_cvref_like_t<decltype(like),decltype(target)>>(target)
#endif