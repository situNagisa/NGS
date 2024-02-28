#pragma once

#include "../defined.h"
#include "../describe/concept.h"

NGS_LIB_MODULE_BEGIN

template<class _Type = void, class _ObjectType = std::remove_reference_t<_Type>>
concept CStructureStorage = requires() {
	requires CStructureDescribe<typename _ObjectType::describe_type>;
	requires (sizeof(_ObjectType) == _ObjectType::describe_type::size);
	requires (alignof(_ObjectType) == _ObjectType::describe_type::align);
};

NGS_LIB_MODULE_END
