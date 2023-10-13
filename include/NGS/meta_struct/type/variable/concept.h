#pragma once

#include "NGS/meta_struct/defined.h"

NGS_META_STRUCT_TYPE_BEGIN

template<class _Variable>
concept CVariable = requires() {
	typename _Variable::original_type;
	typename _Variable::storage_type;
	{ _Variable::size } -> std::convertible_to<size_t>;
	{ _Variable::align } -> std::convertible_to<size_t>;
};

NGS_META_STRUCT_TYPE_END
