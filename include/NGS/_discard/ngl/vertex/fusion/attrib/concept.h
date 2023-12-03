#pragma once

#include "../defined.h"

NGS_NGL_FUSION_BEGIN

template<class _Attrib>
concept CAttrib = requires() {
	{ _Attrib::element_count } -> std::convertible_to<size_t>;
		requires cpt::fundamental<typename _Attrib::element_type>;
};

NGS_NGL_FUSION_END
