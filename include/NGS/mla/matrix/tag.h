#pragma once

#include "NGS/mla/base/tag.h"

NGS_MLA_BEGIN

namespace tag {

struct row : unknown {};
struct column : unknown {};

struct matrix : unknown {};
struct matrix_container : matrix {};
static_assert(std::derived_from<matrix_container, matrix>);

}

NGS_MLA_END
