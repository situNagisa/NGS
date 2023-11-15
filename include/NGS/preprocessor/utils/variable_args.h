#pragma once

#include "../defined.h"

#if defined(NGS_COMPILER_IS_GCC)
#	define NGS_PP_VA_ARGS_OPT_COMMA(...) __VA_OPT__(,) __VA_ARGS__
//#	define NGS_PP_VA_ARGS_OPT_COMMA(...) ##__VA_ARGS__
#elif defined(NGS_COMPILER_IS_MSVC)
#	define NGS_PP_VA_ARGS_OPT_COMMA(...) ,__VA_ARGS__
#else
#	if defined(NGS_CPP_STANDARD_HAS_20)
#		define NGS_PP_VA_ARGS_OPT_COMMA(...) __VA_OPT__(,) __VA_ARGS__
#	else
#		define NGS_PP_VA_ARGS_OPT_COMMA(...) __VA_ARGS__
#	endif
#endif

