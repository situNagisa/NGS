#pragma once

#include "./cv.h"
#include "./reference.h"

NGS_TYPE_TRAIT_BEGIN

template<class _From, class _To>
struct set_same_cvref
{
	using type = set_same_reference_t<_From, set_same_cv_t<std::remove_reference_t<_From>, std::remove_reference_t<_To>>>;
};
template<class _From, class _To>
using set_same_cvref_t = typename set_same_cvref<_From, _To>::type;

NGS_TYPE_TRAIT_END