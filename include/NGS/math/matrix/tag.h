#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

using vectors::tag_trait;
using vectors::tag_trait_t;

//struct matrix_tag : vectors::vector_tag {};
using matrix_tag = vectors::vector_tag;

struct basic_matrix
{
	using ngs_math_vector_type = matrix_tag;
};

NGS_LIB_END