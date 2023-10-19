#pragma once

#include "../describe/concept.h"

NGS_STRUCTURE_TYPE_BEGIN

template<class _Type = void,class _ObjectType = std::remove_reference_t<_Type>>
concept CStructureStorage = requires() {
	requires CStructureDescribe<typename _ObjectType::describe_type>;
	requires (sizeof(_ObjectType) == _ObjectType::describe_type::size);
	requires (alignof(_ObjectType) == _ObjectType::describe_type::align);
};

NGS_STRUCTURE_TYPE_END
