#pragma once

#include "./assert.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

#define NGS_ASSERT_VERIFY(condition,...)							\
do																	\
{																	\
	if (!::ngs::asserts::detail::dynamic_assert((condition),#condition NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__)))	\
	{																\
		NGS_ASSERT_FAIL();											\
	}																\
}while(false)														\
//

NGS_LIB_MODULE_END