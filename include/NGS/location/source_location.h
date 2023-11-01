#pragma once

#include "./defined.h"

NGS_LOCATION_BEGIN

#if !__cpp_lib_source_location
using source_location = std::source_location;
#else

NGS_MODULE_EXPORT struct source_location {
	[[nodiscard]] static consteval source_location current(
		const uint_least32_t line = __builtin_LINE(),
#if defined(NGS_COMPILER_IS_MSVC) || defined(NGS_COMPILER_IS_GCC) || defined(NGS_COMPILER_IS_CLANG)
		const uint_least32_t column = __builtin_COLUMN(),
#else
		const uint_least32_t column = 0,
#endif
		const char* const file = __builtin_FILE(),
#if defined(NGS_COMPILER_IS_CLANG) || defined(NGS_COMPILER_USE_EDG)
		const char* const function = __builtin_FUNCTION()
#else 
		const char* const function = __builtin_FUNCSIG()
#endif
	) noexcept {
		source_location result{};
		result._line = line;
		result._column = column;
		result._file = file;
		result._function = function;
		return result;
	}

	[[nodiscard]] constexpr source_location() noexcept = default;

	[[nodiscard]] constexpr uint_least32_t line() const noexcept {
		return _line;
	}
	[[nodiscard]] constexpr uint_least32_t column() const noexcept {
		return _column;
	}
	[[nodiscard]] constexpr const char* file_name() const noexcept {
		return _file;
	}
	[[nodiscard]] constexpr const char* function_name() const noexcept {
		return _function;
	}

private:
	uint_least32_t _line{};
	uint_least32_t _column{};
	const char* _file = "";
	const char* _function = "";
};

#endif

struct source_location_info {
	constexpr source_location_info() = default;
	constexpr source_location_info(
		const char* const file_name,
		const char* const function_name,
		const uint_least32_t line,
		const uint_least32_t column
	) noexcept :
		file_name(file_name),
		function_name(function_name),
		line(line),
		column(column)
	{}
	constexpr source_location_info(const source_location& location) noexcept :
		source_location_info(
			location.file_name(),
			location.function_name(),
			location.line(),
			location.column()
		)
	{}

	const char* file_name;
	const char* function_name;
	uint_least32_t line;
	uint_least32_t column;
};

NGS_LOCATION_END