#pragma once

#include "NGS/math/mla/base/tag.h"

NGS_MLA_BEGIN

namespace tag {
struct NGS_DLL_API vector : unknown {};
struct NGS_DLL_API vector_container : vector {};

static_assert(std::derived_from<vector_container, vector>);
}


NGS_MLA_END
