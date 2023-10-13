#pragma once

#include "../describe/concept.h"

NGS_META_STRUCT_TYPE_BEGIN

template<class _Structure = void>
concept CStructureStorage = requires() {
	requires CStructureDescribe<typename _Structure::describe_type>;
	requires (sizeof(_Structure) == _Structure::describe_type::size);
	requires (alignof(_Structure) == _Structure::describe_type::align);
};

NGS_META_STRUCT_TYPE_END
