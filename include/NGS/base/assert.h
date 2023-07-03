﻿#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/config.h"
#include "NGS/base/log.h"
#include "NGS/base/utility.h"
#include "NGS/base/type_info.h"

NGS_BEGIN

inline bool Assert(
	bool b,
	nchar_ptr_cst assert_text,
	nstring_view text = "logic error",
	const ngs::source_location& location = ngs::source_location::current()
)
{
	if (b)return false;
	auto [call, return_type, function_id, params] = ParseIdFactor::ParseFunction(location.function_name());

	ngs::Debugger::Print(
		ngs::TextColor::RED,
		ngs::Format(
			""
			"\n========================="
			"\nERROR:: %s"
			"\n文件：%s"
			"\n断言：%s"
			"\n函数：%s"
			"\n  [调用方式]：%s"
			"\n  [返回值  ]：%s"
			"\n  [参数列表]：%s"
			"\n第 %d 行，第 %d 列"
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
		ngs::TextColor::RESERT
	);
	return true;
}

NGS_END


#if NGS_BUILD_TYPE == NGS_DEBUG

#if NGS_COMPILER == NGS_MSVC
#define _NGS_ASSERT_FAIL __debugbreak()
#else
#define _NGS_ASSERT_FAIL abort()
#endif

#define NGS_ASSERT(boolean,...)					\
if(_NGS Assert(boolean, #boolean,__VA_ARGS__))	\
_NGS_ASSERT_FAIL								\
//

#else

#define NGS_ASSERT(...) ((void*)0)

#endif // _DEBUG