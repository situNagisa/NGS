#pragma once

#include "./defined.h"

#if NGS_SYSTEM_IS_WINDOWS
#	include "./impl/windows.hpp"
#elif NGS_SYSTEM_IS_LINUX or NGS_SYSTEM_IS_RTOS
#	include "./impl/linux.hpp"
#elif NGS_SYSTEM_IS_MAC
#	include "./impl/mac.hpp"
#else
#	include "./impl/none.hpp"
#endif