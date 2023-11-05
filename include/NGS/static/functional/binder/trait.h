#pragma once

#include "./concept.h"

NGS_STATIC_FUNCTIONAL_BEGIN

template<class _T>
struct is_bind_expression : std::bool_constant<is_binder<_T>> {};

template<class _T>
inline constexpr bool is_bind_expression_v = is_bind_expression<_T>::value;


NGS_STATIC_FUNCTIONAL_END