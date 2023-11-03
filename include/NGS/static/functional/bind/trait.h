#pragma once

#include "../defined.h"

NGS_FUNCTIONAL_BEGIN

struct binder_tag {};

template<class _T>
concept is_binder = std::derived_from<typename type_traits::object_t<_T>::type_category, binder_tag>;

template<class _T>
struct is_bind_expression : std::bool_constant<is_binder<_T>> {};

template<class _T>
inline constexpr bool is_bind_expression_v = is_bind_expression<_T>::value;


NGS_FUNCTIONAL_END