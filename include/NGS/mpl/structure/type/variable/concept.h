#pragma once

#include "../defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Type = void, class _ObjectType = std::remove_reference_t<_Type>>
concept CVariable = requires() {
	typename _ObjectType::original_type;
	typename _ObjectType::storage_type;
	{ _ObjectType::size } -> std::convertible_to<size_t>;
	{ _ObjectType::align } -> std::convertible_to<size_t>;
};

NGS_LIB_MODULE_END
