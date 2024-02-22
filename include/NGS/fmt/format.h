#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

inline auto format(::std::format_string<> f, auto&&... args)
{
#if defined(NGS_FMT_VALID_STD)
	return ::std::format(f, ::std::forward<decltype(args)>(args)...);
#elif defined(NGS_FMT_VALID_FMT)
	return ::fmt::format(f, ::std::forward<decltype(args)>(args)...);
#endif
}

NGS_LIB_END