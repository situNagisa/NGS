#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl_macro.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(is_template, class, template<class...>class) : std::false_type{};
NGS_mfunction(is_template, template<class...>class _Template, class... _Args) < _Template<_Args...>, _Template > : std::true_type{};


template<class T, template<class...>class _Template>
constexpr bool is_template_v = is_template<T, _Template>::value;

template<class T, template<class...>class _Template>
concept CTemplate = is_template_v<T, _Template>;

NGS_END
NGS_END
