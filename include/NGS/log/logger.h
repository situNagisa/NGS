#pragma once

#include "./scope.h"
#include "./level.h"
#include "./config.h"

NGS_LOG_BEGIN

template<class _Type>
concept is_control_char = cpt::is_any_of<type_traits::naked_t<_Type>, consoles::text_color, log_level>;

struct NGS_DLL_API logger
{
protected:
	using self_type = logger;
public:
	constexpr logger() = default;
	logger(const logger_config& config) : _config(config) {}

	void end_line()
	{
		print('\n');
		_control_char(consoles::text_color::reset);
	}
	void set_print_callback(const std::function<void(std::string_view)>& callback)
	{
		_print_callback = callback;
	}
	//============
	// print
	//============

	void print(auto&& first, auto&&... rest)
	{
		if constexpr (is_control_char<decltype(first)>)
		{
			self_type::_control_char(first);
		}
		else
		{
			self_type::_print(NGS_PP_PERFECT_FORWARD(first));
		}

		if constexpr (sizeof...(rest))
		{
			self_type::print(NGS_PP_PERFECT_FORWARD(rest)...);
		}
	}
	void print_line(auto&&... args)
	{
		self_type::print(NGS_PP_PERFECT_FORWARD(args)...);
		end_line();
	}
	void print_format(std::string_view f, auto&&... args)
	{
		self_type::print(to_strings::format(f, NGS_PP_PERFECT_FORWARD(args)...));
	}
	void print_format_line(std::string_view f, auto&&... args)
	{
		self_type::print_format(f, NGS_PP_PERFECT_FORWARD(args)...);
		end_line();
	}
	//============
	// log
	//============

	void log(log_level level, auto&&... args)
	{
		_control_char(level);
		self_type::print(NGS_PP_PERFECT_FORWARD(args)...);
	}
	void log_line(log_level level, auto&&... args)
	{
		self_type::log(level, NGS_PP_PERFECT_FORWARD(args)...);
		end_line();
	}
	void log_format(log_level level, std::string_view f, auto&&... args)
	{
		///\code NGS_ format\endcode remove ADL
		self_type::log(level, to_strings::format(f, NGS_PP_PERFECT_FORWARD(args)...));
	}
	void log_format_line(log_level level, std::string_view f, auto&&... args)
	{
		self_type::log_format(level, f, NGS_PP_PERFECT_FORWARD(args)...);
		end_line();
	}
	//=============
	NGS_CONSTEXPR26 consoles::text_color level_color(log_level level) const { return _config.level_colors.at(level); }
	constexpr auto&& get_config()const { return _config; }
	constexpr auto&& get_config() { return _config; }

#if (defined(NGS_COMPILER_IS_GCC) and NGS_COMPILER_VERSION_IS_AT_LEAST(12, 0)) or !defined(NGS_COMPILER_IS_GCC)
	constexpr
#endif
		void set_scope_name(std::string_view name)
	{
		_current_scope_name = name;
	}
private:
	void _control_char(consoles::text_color color)
	{
		_console.set_text_color(color);
	}
	void _control_char(log_level level)
	{
		if (_config.enable_print.time)
		{
			const auto now = std::chrono::system_clock::now();
			std::time_t now_c = std::chrono::system_clock::to_time_t(now);
			_print(std::put_time(std::localtime(&now_c), "%F %T "));

		}

		_print('[');
		_control_char(level_color(level));
		_print(to_strings::to_string(level));
		_control_char(consoles::text_color::reset);
		_print(']');

		if (_config.enable_print.scope_name)
		{
			_print(' ');
			_control_char(level_color(level));
			_print(_current_scope_name);
			_control_char(consoles::text_color::reset);
			_print(" : ");
		}
	}

	void _print(auto&& first)
	{
		if constexpr (requires{ _print_callback(NGS_PP_PERFECT_FORWARD(first)); })
		{
			_print_callback(NGS_PP_PERFECT_FORWARD(first));
		}
		else if constexpr (requires{ to_strings::to_string(NGS_PP_PERFECT_FORWARD(first)); })
		{
			_print_callback(to_strings::to_string(NGS_PP_PERFECT_FORWARD(first)));
		}
		//else if constexpr (requires(std::stringstream o) { o << NGS_PP_PERFECT_FORWARD(first); })
		//{
		//	std::stringstream buffer{};
		//	buffer << NGS_PP_PERFECT_FORWARD(first);
		//	_print_callback(buffer.str());
		//}
		else
		{
			static_assert(cpt::none<decltype(first)>, "unsupported type");
		}
	}
private:
	logger_config _config{};
	consoles::default_console _console{};
	std::function<void(std::string_view)> _print_callback = [](std::string_view info)
		{
			std::cout << info << std::flush;
		};
	std::string _current_scope_name{};
};

inline logger std_logger{};

#if NGS_BUILD_TYPE_IS_DEBUG

#define NGS_LOG_CALL(function,...)				\
do												\
{												\
	NGS_ logs::std_logger.set_scope_name(NGS_PP_FUNCTION_NAME);\
	NGS_ logs::std_logger.function(__VA_ARGS__);\
} while (false)									\
//

#else

#define NGS_LOG_CALL(function,...) (static_cast<void*>(nullptr))

#endif


#define NGS_PRINT(...)				NGS_LOG_CALL(print,__VA_ARGS__)
#define NGS_PRINTL(...)				NGS_LOG_CALL(print_line,__VA_ARGS__)
#define NGS_PRINTF(format,...)		NGS_LOG_CALL(print_format,format,__VA_ARGS__)
#define NGS_PRINTFL(format,...)		NGS_LOG_CALL(print_format_line,format,__VA_ARGS__)

#define NGS_LOG(level,...)									\
NGS_LOG_CALL(log,NGS_ logs::log_level::level, __VA_ARGS__)	\
//
#define NGS_LOGL(level,...)									\
NGS_LOG_CALL(log_line,NGS_ logs::log_level::level, __VA_ARGS__)\
//
#define NGS_LOGF(level,format,...)							\
NGS_LOG_CALL(log_format,NGS_ logs::log_level::level, format NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__))\
//
#define NGS_LOGFL(level,format,...)							\
NGS_LOG_CALL(log_format_line,NGS_ logs::log_level::level, format NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__))\
//


NGS_LOG_END
