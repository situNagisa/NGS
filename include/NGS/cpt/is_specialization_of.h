#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class _T, template<class...>class _Template>
concept is_specialization_of = type_traits::is_specialization_v<_T, _Template>;

NGS_CPT_END