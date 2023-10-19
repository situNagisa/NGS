﻿#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/log.h"
#include "NGS/base/format.h"
#include "NGS/base/type_info.h"

NGS_BEGIN

inline bool Assert(
	bool b,
	nchar_ptr_cst assert_text,
	nstring_view text = "logic error",
	const source_location& location = source_location::current()
)
{
	if (b)return false;
	auto [call, return_type, function_id, params] = ParseIdFactor::ParseFunction(location.function_name());

	Debugger::Print(
		TextColor::red,
		format(
			""
			"\n========================="
			"\nERROR:: %s"
			"\nfile    : %s"
			"\nassert  : %s"
			"\nfunction: %s"
			"\n  [call   ]: %s"
			"\n  [return ]: %s"
			"\n  [params ]: %s"
			"\nline %d,column %d"
			"\n=========================\n",
			text.data(),
			location.file_name(),
			assert_text,
			function_id.c_str(),
			call.c_str(),
			return_type.c_str(),
			params.c_str(),
			location.line(),
			location.column()
		),
		TextColor::reset
	);
	return true;
}

NGS_END


#if NGS_BUILD_TYPE == NGS_DEBUG

#if NGS_COMPILER == NGS_MSVC
#define _NGS_ASSERT_FAIL __debugbreak()
#else
#define _NGS_ASSERT_FAIL exit(1)
#endif

#if NGS_COMPILER == NGS_GCC

#define NGS_ASSERT(boolean,...)					\
if(_NGS Assert(boolean, #boolean,##__VA_ARGS__))\
_NGS_ASSERT_FAIL								\
//

#else

#define NGS_ASSERT(boolean,...)								\
do {														\
	if constexpr (!std::is_constant_evaluated()) {			\
		if (_NGS Assert(boolean, #boolean, __VA_ARGS__))	\
			_NGS_ASSERT_FAIL;								\
	}														\
}while(false)												\
//

#endif

#else

#define NGS_ASSERT(...) (void)

#endif // _DEBUG