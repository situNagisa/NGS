//==========================================================================================================
// @file	:	NGS/NGS_Config
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:23:33
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_NGS_Config
#define __HEAD_NGS_NGS_Config

#include "NGS/base/version.h"

#ifdef NGS_HAS_CPP_17
#define NGS_INLINE inline
#elif //NGS_HAS_CPP17
#define NGS_INLINE
#endif  //NGS_HAS_CPP17

#ifdef NGS_HAS_CPP_17


#elif //NGS_HAS_CPP17


#endif  //NGS_HAS_CPP17

#define NGS_DEBUG 0
#define NGS_RELEASE 1

#ifdef _DEBUG || Debug
#define NGS_BUILD_TYPE NGS_DEBUG
#else
#define NGS_BUILD_TYPE NGS_RELEASE
#endif

#endif // !__HEAD_NGS_NGS_Config
