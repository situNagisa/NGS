﻿#pragma once

#include "./to_string.h"
#include "../config.h"

#if NGS_COMPILER == NGS_MSVC

#	define NGS_THROW_WARNING(code, msg)			__pragma(message(__FILE__ "("  NGS_TO_STRING(__LINE__) ")" ": warning C" NGS_TO_STRING(code) ": " msg))
#	define NGS_THROW_ERROR(level, code, msg)	__pragma(message(__FILE__ "("  NGS_TO_STRING(__LINE__) ")" ":" level " error C" ___AUX_STR(code) ": " msg))

#else

#	define NGS_THROW_WARNING(code, msg)	
#	define throw_error(level, code, msg)

#endif