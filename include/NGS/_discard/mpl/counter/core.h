#pragma once

#include "./defined.h"

NGS_MPL_COUNTER_BEGIN

template<std::size_t _Index>
struct reader
{
    friend auto counted_flag(reader<_Index>);
};

template<std::size_t _Index>
struct setter
{
    friend auto counted_flag(reader<_Index>) {}
   std::size_t value = _Index;
};

template<auto _Index = 0,auto _Tag = [] {},bool _Condition = requires(reader<_Index> red) { counted_flag(red); } >
consteval auto next()
{
    if constexpr (!_Condition)
    {
        constexpr setter<_Index> s;
        return s.value;
    }
    else
    {
        return next<_Index + 1>();
    }
}

NGS_MPL_COUNTER_END
