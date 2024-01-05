#pragma once

#include "./depth.h"
#include "./tag.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
inline constexpr bool enable_operator_matrix = false;

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

template<class _M>
concept operator_matrix = pure_matrix<_M> && ((scalar_matrix<_M> && tag_matrix<_M>) || enable_operator_matrix<_M>);

NGS_LIB_MODULE_END