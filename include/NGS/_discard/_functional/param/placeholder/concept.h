#pragma once

#include "../../index.h"
#include "./trait.h"
#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template <class _T>
concept is_placeholder = is_param<_T> && requires{ { placeholder_traits<_T>::index } -> std::convertible_to<index_t>; };

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(is_placeholder);

template<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::is_placeholder _T>
struct NGS_NS::type_traits::storage<_T&> { using type = _T; };

template<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::is_placeholder _T>
struct NGS_NS::type_traits::storage<_T&&> { using type = _T; };

template<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::is_placeholder _T>
struct NGS_NS::type_traits::restored<_T&> { using type = _T; };

template<NGS_NS::NGS_LIB_NAME::NGS_LIB_MODULE_NAME::is_placeholder _T>
struct NGS_NS::type_traits::restored<_T&&> { using type = _T; };