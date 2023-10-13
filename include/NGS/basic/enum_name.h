#pragma once

#include "./defined.h"

NGS_BEGIN

template<auto value>
constexpr auto enum_name()
{
    std::string_view name;
#if NGS_COMPILER == NGS_CLANG
    name = __PRETTY_FUNCTION__;
    auto start = name.find("value = ") + 8; // 8 is length of "value = "
    auto end = name.find_last_of(']');
    return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER == NGS_GCC
    name = __PRETTY_FUNCTION__;
    auto start = name.find("value = ") + 8; // 8 is length of "value = "
    auto end = name.find_last_of(']');
    return std::string_view{ name.data() + start, end - start };

#elif NGS_COMPILER == NGS_MSVC
    name = __FUNCSIG__;
    auto start = name.find("enum_name<") + 10; // 10 is length of "enum_name<"
    auto end = name.find_last_of('>');
    return std::string_view{ name.data() + start, end - start };
#endif
}

NGS_END
