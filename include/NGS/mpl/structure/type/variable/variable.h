#pragma once

#include "./concept.h"

NGS_LIB_MODULE_BEGIN

/// @brief 包装类型为`元变量`
/// @note
///		1) 若`_Type`为`元变量`，则`variable`为`_Type`
///		2) 否则返回`_Type`的`元变量`包装
NGS_MPL_FUNCTION(variable, class _Type) {
	NGS_MPL_TYPE original_type = _Type;
	NGS_MPL_TYPE storage_type = std::remove_reference_t<_Type>;
	NGS_MPL_VALUE size_t size = layout::size_of<storage_type>();
	NGS_MPL_VALUE size_t align = layout::align_of<storage_type>();
};

NGS_MPL_FUNCTION(variable, CVariable _Variable) < _Variable > : _Variable{};

NGS_CCPT_VERIFY(CVariable, variable<int>);

NGS_LIB_MODULE_END
