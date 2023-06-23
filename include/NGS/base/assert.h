#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/config.h"
#include "NGS/base/log.h"

NGS_BEGIN

inline void Assert(
	bool b,
	nchar_ptr_cst assert_text,
	nchar_ptr_cst text = "logic error",
	const ngs::source_location& location = ngs::source_location::current()
)
{
	if (b)return;
	ngs::Debugger::Print(
		ngs::TextColor::RED,
		ngs::Format(
			""
			"\n========================="
			"\nERROR::[ %s ]"
			"\n文件：%s"
			"\n断言：%s"
			"\n函数：%s"
			"\n第 %d 行，第 %d 列"
			"\n=========================\n",
			text,
			location.file_name(),
			assert_text,
			location.function_name(),
			location.line(),
			location.column()
		),
		ngs::TextColor::RESERT
	);
#if NGS_COMPILER == NGS_MSVC
	__debugbreak();
#else
	abort();
#endif
}

NGS_END


#if NGS_BUILD_TYPE == NGS_DEBUG

#define NGS_ASSERT(boolean,...) _NGS Assert(boolean, #boolean,__VA_ARGS__)

#else

#define NGS_ASSERT(...) ((void*)0)

#endif // _DEBUG