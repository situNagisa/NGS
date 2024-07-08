#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::basic_stringable;
using details::stringable;
using details::wstringable;
#ifdef __cpp_lib_char8_t
using details::u8stringable;
#endif
using details::u16stringable;
using details::u32stringable;

using details::basic_to_string;
using details::to_string;
using details::to_wstring;
#ifdef __cpp_lib_char8_t
using details::to_u8string;
#endif
using details::to_u16string;
using details::to_u32string;

NGS_LIB_END