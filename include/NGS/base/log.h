#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/base_class.h"
#include "NGS/base/format.h"
#include "NGS/base/type_info.h"
#include "NGS/base/to_string.h"

NGS_BEGIN

enum DLevel {
	trace,
	debug,
	info,
	warning,
	error,
	fatal,
};

enum class  TextColor {
	reset,
	black,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white,
};

class NGS_DLL_API  Debugger {
public:
	class  ScopeHolder : DeleteCopy {
	public:
		friend class  Debugger;
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
		TextColor color = TextColor::white;
		switch (level)
		{
		case DLevel::trace:
			color = TextColor::white;
			break;
		case DLevel::debug:
			color = TextColor::green;
			break;
		case DLevel::info:
			color = TextColor::cyan;
			break;
		case DLevel::warning:
			color = TextColor::yellow;
			break;
		case DLevel::error:
			color = TextColor::red;
			break;
		case DLevel::fatal:
			color = TextColor::red;
			break;
		default:
			break;
		}
		Print(color, GetCurrentFunctionName(), TextColor::white, " -- ", std::forward<Args>(args)..., TextColor::reset);
	}
	template<typename... Args>
	static void LogLine(DLevel level, Args&&... args) {
		Log(level, std::forward<Args>(args)..., "\n");
	}
	template<typename... Args>
	static void LogFormat(DLevel level, const char* fmt, Args&&... args) {
		Log(level, format(fmt, std::forward<Args>(args)...));
	}
	template<typename... Args>
	static void LogFormatLine(DLevel level, const char* format, Args&&... args) {
		LogFormat(level, format, std::forward<Args>(args)...);
		PrintLine();
	}

	template<typename...Args>
	static void Print(Args&&... args) {
		if (_disable)return;
		std::lock_guard<std::mutex> lock(_mutex);
		_Print(std::forward<Args>(args)...);
	}
	template<typename... Args>
	static void PrintLine(Args&&... args) {
		Print(std::forward<Args>(args)..., "\n");
	}
	template<typename... Args>
	static void PrintFormat(const char* fmt, Args&&... args) {
		Print(format(fmt, std::forward<Args>(args)...));
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
		if constexpr (std::same_as<std::remove_cvref_t<T>, TextColor>) {
			set_text_color(obj);
		}
		else if constexpr (requires{ std::cout << to_string(std::forward<T>(obj)); }) {
			std::cout << to_string(std::forward<T>(obj));
		}
		else {
			std::cout << std::forward<T>(obj);
		}


		if constexpr (sizeof...(Args))_Print(std::forward<Args>(args)...);
	}
public:
	inline static std::function<void(TextColor)> set_text_color = [](TextColor) {};

	inline static std::stack<std::string> prefix;
private:
	inline static std::vector<const ScopeHolder*> _stack;
	inline static size_t _disable = 0;
	inline static std::mutex _mutex{};
};

#if NGS_BUILD_TYPE_IS_DEBUG

#define NGS_LOG_SCOPE_CREATE auto _ngs_scope_holder = NGS_ Debugger::Push()
#define NGS_LOG_SCOPE_DISABLE NGS_LOG_SCOPE_CREATE;_ngs_scope_holder.Disable()
#define NGS_LOG_SCOPE_ENABLE _ngs_scope_holder.Enable()

#define _NGS_DEBUG_CALL(function, ...)			\
do {											\
	NGS_LOG_SCOPE_CREATE;						\
	NGS_ Debugger::function(__VA_ARGS__);		\
} while (false)									\
//

#define NGS_LOG(level, ...)						\
_NGS_DEBUG_CALL(Log, NGS_ level, ##__VA_ARGS__)	
#define NGS_LOGL(level, ...)					\
_NGS_DEBUG_CALL(LogLine, NGS_ level, ##__VA_ARGS__)	
#define NGS_LOGF(level, format, ...) 			\
_NGS_DEBUG_CALL(LogFormat, NGS_ level, format, ##__VA_ARGS__)	
#define NGS_LOGFL(level, format, ...)					\
_NGS_DEBUG_CALL(LogFormatLine, NGS_ level, format, ##__VA_ARGS__)	\
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
