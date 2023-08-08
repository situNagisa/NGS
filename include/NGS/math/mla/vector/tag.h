#pragma once

#include "NGS/math/mla/base/tag.h"

NGS_MLA_BEGIN

namespace tag {
struct vector : unknown {};
struct vector_container : vector {};

static_assert(std::derived_from<vector_container, vector>);
}


NGS_MLA_END
