//==========================================================================================================
// @file	:	NGS/NGS
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:04:40
// @brief	:	
//==========================================================================================================
#pragma once

//NGS_USE_HPP
//NGS_USE_EMBEDDED
//NGS_USE_NSL
//NGS_USE_NSW

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"
#include "NGS/algorithm/algorithm.h"

#ifdef NGS_USE_EMBEDDED
#include "NGS/embedded/embedded.h"
#endif

#ifdef NGS_USE_NSL
#include "NGS/nsl/NSL.h"
#endif

#ifdef NGS_USE_NSW
#include "NGS/nsw/NSW.h"
#endif

#if _MSC_VER

//#pragma comment(lib,"NGS.lib")

#endif // USE_NGS_MODULE
