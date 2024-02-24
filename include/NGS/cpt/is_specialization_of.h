#pragma once

#include "./defined.h"

NGS_CPT_BEGIN

template<class T, template<class...>class Template>
concept is_specialization_of = type_traits::is_specialization_v<T, Template>;

template<class T, template<class...>class Template>
concept derived_from_specialization = type_traits::is_derived_from_specialization_v<T, Template>;

NGS_CPT_END