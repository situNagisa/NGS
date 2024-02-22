#pragma once

#include "NGS/basic/basic.h"
#include "NGS/to_string/to_string.h"

#if defined(__cpp_lib_format)
#	define NGS_FMT_VALID_STD 1
//#	include <format>
#else
#	if !__has_include(<fmt/format.h>)
#		error "fmt is not available"
#	else
#		define NGS_FMT_VALID_FMT 1
#		include <fmt/core.h>
//#		include <fmt/chrono.h>
#	endif
#endif


#define NGS_FMT_NS fmt

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0

#define NGS_LIB_NAME NGS_FMT_NS
#include "NGS/lib/lib.h"