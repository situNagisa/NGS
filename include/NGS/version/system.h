#pragma once

#define NGS_SYSTEM_UNKNOWN	(0)
#define NGS_SYSTEM_WINDOWS	(1)
#define NGS_SYSTEM_LINUX	(2)
#define NGS_SYSTEM_MAC		(3)
#define NGS_SYSTEM_RTOS		(4)

#if defined(_WIN32) or defined(_WIN64) or defined(_WIN32_WINNT)

#	define NGS_SYSTEM_IS_WINDOWS true
#	define NGS_SYSTEM NGS_SYSTEM_WINDOWS

#elif defined(__linux__)

#	define NGS_SYSTEM_IS_LINUX true
#	define NGS_SYSTEM NGS_SYSTEM_LINUX

#elif defined(__APPLE__)

#	define NGS_SYSTEM_IS_MAC true
#	define NGS_SYSTEM NGS_SYSTEM_MAC

#elif defined(ESP_PLATFORM)

#	define NGS_SYSTEM_IS_ESP true
#	define NGS_SYSTEM_IS_RTOS true
#	define NGS_SYSTEM NGS_SYSTEM_RTOS

#else

#	define NGS_SYSTEM NGS_SYSTEM_UNKNOWN

#	warning "unknown system"

#endif