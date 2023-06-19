#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/config.h"
#include "NGS/base/log.h"



#if NGS_BUILD_TYPE == NGS_DEBUG

inline void NGS_Assert(
	bool b,
	ngs::nchar_ptr_cst text = "logic error",
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
			"\n函数：%s"
			"\n第 %d 行，第 %d 列"
			"\n=========================\n",
			text,
			location.file_name(),
			location.function_name(),
			location.line(),
			location.column()
		),
		ngs::TextColor::RESERT
	);
	abort();
}

#else

#define NGS_Assert(...) ((void*)0)

#endif // _DEBUG