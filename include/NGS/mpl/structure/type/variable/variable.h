#pragma once

#include "./concept.h"

NGS_STRUCTURE_TYPE_BEGIN

NGS_MPL_FUNCTION(variable, class _Type) {
	NGS_MPL_TYPE original_type = _Type;
	NGS_MPL_TYPE storage_type = std::remove_reference_t<_Type>;
	NGS_MPL_VALUE size_t size = layout::size_of<storage_type>();
	NGS_MPL_VALUE size_t align = layout::align_of<storage_type>();
};

NGS_MPL_FUNCTION(variable, CVariable _Variable) < _Variable > : _Variable{};

NGS_CCPT_VERIFY(CVariable, variable<int>);

NGS_STRUCTURE_TYPE_END
