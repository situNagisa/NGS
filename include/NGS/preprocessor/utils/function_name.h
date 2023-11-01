﻿#pragma once

#include "../defined.h"

#if NGS_COMPILER_IS_MSVC
#	define NGS_PP_PRETTY_FUNCTION_NAME __FUNCSIG__
#elif NGS_COMPILER_IS_GCC
#	define NGS_PP_PRETTY_FUNCTION_NAME __PRETTY_FUNCTION__
#elif NGS_COMPILER_IS_CLANG
#	define NGS_PP_PRETTY_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#	define NGS_PP_PRETTY_FUNCTION_NAME __func__
#endif

#if NGS_COMPILER_IS_MSVC
#	define NGS_PP_FUNCTION_NAME __FUNCTION__
#elif NGS_COMPILER_IS_GCC
#	define NGS_PP_FUNCTION_NAME __FUNCTION__
#elif NGS_COMPILER_IS_CLANG
#	define NGS_PP_FUNCTION_NAME __FUNCTION__
#else
#	define NGS_PP_FUNCTION_NAME __func__
#endif