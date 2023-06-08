#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/config.h"
#include "NGS/base/base_class.h"
#include "NGS/base/console.h"

NGS_BEGIN

enum DLevel {
	trace,
	debug,
	info,
	warning,
	error,
	fatal,
};

class Debugger {
public:
	class ScopeHolder : DeleteCopy {
	public:
		friend class Debugger;
		~ScopeHolder() {
			if (_disable)Debugger::_disable--;
			Debugger::_Pop();
		}
		void Disable() {
			Debugger::_disable++;
			_disable = true;
		}
	private:
		ScopeHolder(const source_location& source)
			: _line(source.line())
			, _column(source.column())
			, _file(source.file_name())
			, _function(source.function_name())
		{
			Debugger::_Push(*this);
		}
		std::string GetFunctionName()const {
			auto start = _function.find("(");
			auto end = _function.rfind(" ", start) + 1;
			return _function.substr(end, start - end);
		}
	public:
		size_t _line = 0;
		size_t _column = 0;
		std::filesystem::path _file = {};
		std::string _function = {};
		bool _disable = false;
	};
public:
	static ScopeHolder Push(const source_location& source = source_location::current()) { return ScopeHolder{ source }; }
	static std::string GetCurrentFunctionName() { return _stack.back()->GetFunctionName(); }
	static bool Enable() { return !_disable; }

#if NGS_COMPILER == NGS_MSVC
#define vprint vsprintf_s
#else
#define vprint vsprintf
#endif

	template<typename... Args>
	static void Log(DLevel level, Args&&... args) {
		if (_disable)return;
		Console::Color color;
		switch (level)
		{
		case DLevel::trace:
			color = Console::Color::WHITE;
			break;
		case DLevel::debug:
			color = Console::Color::GREEN;
			break;
		case DLevel::info:
			color = Console::Color::CYAN;
			break;
		case DLevel::warning:
			color = Console::Color::YELLOW;
			break;
		case DLevel::error:
			color = Console::Color::RED;
			break;
		case DLevel::fatal:
			color = Console::Color::RED;
			break;
		default:
			break;
		}
		_Print(color, GetCurrentFunctionName(), Console::Color::WHITE, " -- ", args..., Console::Color::RESERT);
	}
	template<typename... Args>
	static void LogLine(DLevel level, Args&&... args) {
		Log(level, args..., "\n");
	}
	static void LogFormat(DLevel level, const char* format, ...) {
		nchar buffer[1024];
		va_list args;
		va_start(args, format);
		vprint(buffer, format, args);
		va_end(args);
		Log(level, buffer);
	}

	static void LogFormatLine(DLevel level, const char* format, ...) {
		va_list args;
		va_start(args, format);
		LogFormat(level, format, args);
		va_end(args);
		_Print("\n");
	}

	template<typename... Args>
	static void Print(DLevel level, Args&&... args) {
		if (_disable)return;
		Console::Color color;
		switch (level)
		{
		case DLevel::trace:
			color = Console::Color::WHITE;
			break;
		case DLevel::debug:
			color = Console::Color::GREEN;
			break;
		case DLevel::info:
			color = Console::Color::CYAN;
			break;
		case DLevel::warning:
			color = Console::Color::YELLOW;
			break;
		case DLevel::error:
			color = Console::Color::RED;
			break;
		case DLevel::fatal:
			color = Console::Color::RED;
			break;
		default:
			break;
		}
		_Print(color, args..., Console::Color::RESERT);
	}
	template<typename... Args>
	static void PrintLine(DLevel level, Args&&... args) {
		Print(level, args..., "\n");
	}
	static void PrintFormat(DLevel level, const char* format, ...) {
		nchar buffer[1024];
		va_list args;
		va_start(args, format);
		vprint(buffer, format, args);
		va_end(args);
		Print(level, buffer);
	}

	static void PrintFormatLine(DLevel level, const char* format, ...) {
		va_list args;
		va_start(args, format);
		PrintFormat(level, format, args);
		va_end(args);
		_Print("\n");
	}
#undef vprint
public:
	static void _Push(const ScopeHolder& holder) { _stack.push_back(&holder); }
	static void _Pop() { _stack.pop_back(); }

	template<typename T, typename... Args>

	static void _Print(T&& obj, Args&&... args) {
		std::cout << std::forward<T>(obj);
		if constexpr (sizeof...(Args))_Print(args...);
	}

	template<std::convertible_to<std::string> T, typename... Args>
	static void _Print(T&& obj, Args&&... args) {
		std::cout << std::string(std::forward<T>(obj));
		if constexpr (sizeof...(Args))_Print(args...);
	}
	template<typename... Args>
	static void _Print(const Console::Color& color, Args&&... args) {
		Console::SetTextColor(color);
		if constexpr (sizeof...(Args))_Print(args...);
	}

public:
	inline static std::vector<const ScopeHolder*> _stack;
	inline static size_t _disable = 0;
};

#if NGS_BUILD_TYPE == NGS_DEBUG

#define NGS_SCOPE_CREATE auto _ngs_scope_holder = _NGS Debugger::Push()
#define NGS_SCOPE_DISABLE NGS_SCOPE_CREATE;_ngs_scope_holder.Disable()
#define NGS_LOG(level, ...)						\
do {											\
	NGS_SCOPE_CREATE;							\
	_NGS Debugger::Log(level, ##__VA_ARGS__);	\
} while (0)										\
//

#define NGS_LOGL(level, ...)					\
do {											\
	NGS_SCOPE_CREATE;							\
	_NGS Debugger::LogLine(level, ##__VA_ARGS__);\
} while (0)										\
//
#define NGS_LOGF(level, format, ...) 			\
do {											\
	NGS_SCOPE_CREATE;							\
	_NGS Debugger::LogFormat(level,format, ##__VA_ARGS__);\
} while (0)										\
//

#define NGS_LOGFL(level, format, ...)					\
do {													\
	NGS_SCOPE_CREATE;									\
	_NGS Debugger::LogFormatLine(level,format, ##__VA_ARGS__);\
} while (0)												\
//

#else

#define NGS_DEBUG_SCOPE_HOLDER
#define NGS_SCOPE_HOLDER_DISABLE
#define NGS_LOG(level, ...) 
#define NGS_LOGL(level, ...) 
#define NGS_LOGF(level, format, ...) 
#define NGS_LOGFL(level, format, ...)

#endif



NGS_END
