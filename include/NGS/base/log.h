#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/config.h"
#include "NGS/base/base_class.h"
#include "NGS/base/utility.h"
#include "NGS/base/type_info.h"

NGS_BEGIN

enum DLevel {
	trace,
	debug,
	info,
	warning,
	error,
	fatal,
};

enum class TextColor {
	RESERT,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
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
		void Enable() {
			Debugger::_disable--;
			_disable = false;
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
			return ParseIdFactor::GetFunctionName(_function);
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

	template<typename... Args>
	static void Log(DLevel level, Args&&... args) {
		TextColor color;
		switch (level)
		{
		case DLevel::trace:
			color = TextColor::WHITE;
			break;
		case DLevel::debug:
			color = TextColor::GREEN;
			break;
		case DLevel::info:
			color = TextColor::CYAN;
			break;
		case DLevel::warning:
			color = TextColor::YELLOW;
			break;
		case DLevel::error:
			color = TextColor::RED;
			break;
		case DLevel::fatal:
			color = TextColor::RED;
			break;
		default:
			break;
		}
		Print(color, GetCurrentFunctionName(), TextColor::WHITE, " -- ", std::forward<Args>(args)..., TextColor::RESERT);
	}
	template<typename... Args>
	static void LogLine(DLevel level, Args&&... args) {
		Log(level, std::forward<Args>(args)..., "\n");
	}
	template<typename... Args>
	static void LogFormat(DLevel level, const char* fmt, Args&&... args) {
		Log(level, Format(fmt, std::forward<Args>(args)...));
	}
	template<typename... Args>
	static void LogFormatLine(DLevel level, const char* format, Args&&... args) {
		LogFormat(level, format, std::forward<Args>(args)...);
		PrintLine();
	}

	template<typename...Args>
	static void Print(Args&&... args) {
		if (_disable)return;
		_Print(std::forward<Args>(args)...);
	}
	template<typename... Args>
	static void PrintLine(Args&&... args) {
		Print(std::forward<Args>(args)..., "\n");
	}
	template<typename... Args>
	static void PrintFormat(const char* fmt, Args&&... args) {
		Print(Format(fmt, std::forward<Args>(args)...));
	}
	template<typename... Args>
	static void PrintFormatLine(const char* format, Args&&... args) {
		PrintFormat(format, std::forward<Args>(args)...);
		PrintLine();
	}
public:
	static void _Push(const ScopeHolder& holder) { _stack.push_back(&holder); }
	static void _Pop() { _stack.pop_back(); }

	template<typename T, typename... Args>
	static void _Print(T&& obj, Args&&... args) {
		if constexpr (std::same_as<std::decay_t<T>, TextColor>) {
			set_text_color(obj);
		}
		else if constexpr (std::convertible_to<T, std::string>) {
			std::cout << std::string(std::forward<T>(obj));
		}
		else {
			std::cout << std::forward<T>(obj);
		}

		if constexpr (sizeof...(Args))_Print(std::forward<Args>(args)...);
	}
public:
	inline static std::function<void(TextColor)> set_text_color = [](TextColor) {};

private:
	inline static std::vector<const ScopeHolder*> _stack;
	inline static size_t _disable = 0;
};

#if NGS_BUILD_TYPE == NGS_DEBUG

#define NGS_LOG_SCOPE_CREATE auto _ngs_scope_holder = _NGS Debugger::Push()
#define NGS_LOG_SCOPE_DISABLE NGS_LOG_SCOPE_CREATE;_ngs_scope_holder.Disable()
#define NGS_LOG_SCOPE_ENABLE _ngs_scope_holder.Enable()

#define _NGS_DEBUG_CALL(function, ...)			\
do {											\
	NGS_LOG_SCOPE_CREATE;							\
	_NGS Debugger::function(__VA_ARGS__);		\
} while (0)										\
//

#define NGS_LOG(level, ...)						\
_NGS_DEBUG_CALL(Log, _NGS level, ##__VA_ARGS__)	
#define NGS_LOGL(level, ...)					\
_NGS_DEBUG_CALL(LogLine, _NGS level, ##__VA_ARGS__)	
#define NGS_LOGF(level, format, ...) 			\
_NGS_DEBUG_CALL(LogFormat, _NGS level, format, ##__VA_ARGS__)	
#define NGS_LOGFL(level, format, ...)					\
_NGS_DEBUG_CALL(LogFormatLine, _NGS level, format, ##__VA_ARGS__)	\
//

#define NGS_PRINT(...)							\
_NGS_DEBUG_CALL(Print, ##__VA_ARGS__)			
#define NGS_PRINTL(...)							\
_NGS_DEBUG_CALL(PrintLine, ##__VA_ARGS__)		
#define NGS_PRINTF(format, ...)					\
_NGS_DEBUG_CALL(PrintFormat, format, ##__VA_ARGS__)	
#define NGS_PRINTFL(format, ...)				\
_NGS_DEBUG_CALL(PrintFormatLine, format, ##__VA_ARGS__)	\
//

#else

#define NGS_LOG_SCOPE_CREATE
#define NGS_LOG_SCOPE_DISABLE
#define NGS_LOG_SCOPE_ENABLE

#define NGS_LOG(level, ...) 
#define NGS_LOGL(level, ...) 
#define NGS_LOGF(level, format, ...) 
#define NGS_LOGFL(level, format, ...)

#define NGS_PRINT(...)
#define NGS_PRINTL(...)
#define NGS_PRINTF(format, ...)
#define NGS_PRINTFL(format, ...)

#endif



NGS_END
