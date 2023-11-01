#pragma once

#include "../defined.h"


#if defined(__cpp_modules) && defined(BUILD_NGS_MODULE)
#	define NGS_MODULE_EXPORT export
#else
#	define NGS_MODULE_EXPORT
#endif