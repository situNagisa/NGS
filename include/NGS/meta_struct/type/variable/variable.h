#pragma once

#include "./concept.h"

NGS_META_STRUCT_TYPE_BEGIN

NGS_mfunction(variable, class _Type) {
	NGS_mcst_t original_type = _Type;
	NGS_mcst_t storage_type = std::remove_reference_t<_Type>;
	NGS_mcst size_t size = layout::size_of<storage_type>();
	NGS_mcst size_t align = layout::align_of<storage_type>();
};

NGS_mfunction(variable, CVariable _Variable) < _Variable > : _Variable{};

NGS_CCPT_VERIFY(CVariable, variable<int>);

NGS_META_STRUCT_TYPE_END
