#pragma once

#include "./defined.h"

NGS_ASSERT_BEGIN

inline bool dynamic_assert(
	bool condition,
	std::string_view expression,
	std::string_view message = "",
	const locations::source_location& location = locations::source_location::current()
)
{
	if (condition)
	{
		return false;
	}

	logs::std_logger.print_line(
		consoles::text_color::red,
		format(
			""
			"\n========================="
			"\nERROR:: %s"
			"\nfile    : %s"
			"\nassert  : %s"
			"\nfunction: %s"
			"\nline %d,column %d"
			"\n=========================",
			message.data(),
			location.file_name(),
			expression.data(),
			location.function_name(),
			location.line(),
			location.column()
		),
		consoles::text_color::reset
	);
	return true;
}

template<bool _Condition, static_strings::static_string _Message = "", locations::source_location_info _Location = locations::source_location::current()>
constexpr bool static_assert_()
{
	return _Condition;
}

constexpr bool assert_(
	bool condition,
	std::string_view expression,
	std::string_view message = "",
	const locations::source_location& location = locations::source_location::current()
)
{
	if (std::is_constant_evaluated())
	{
		return condition;
	}
	else
	{
		return dynamic_assert(condition, expression, message, location);
	}
}

NGS_ASSERT_END

#if NGS_COMPILER_IS_MSVC && NGS_BUILD_TYPE_IS_DEBUG

#	define NGS_ASSERT_FAIL __debugbreak()

#else

#	define NGS_ASSERT_FAIL std::abort()

#endif

#if NGS_BUILD_TYPE_IS_DEBUG

#define NGS_ASSERT(condition,...)									\
do																	\
{																	\
	if (NGS_ asserts::dynamic_assert((condition),#condition,__VA_ARGS__))\
	{																\
		NGS_ASSERT_FAIL;											\
	}																\
}while(false)														\
//

#	if NGS_CPP_STANDARD_HAS_20
#define NGS_ASSERT_IF_CONSTEVAL(condition,...)									\
do																				\
{																				\
	if(std::is_constant_evaluated())											\
	{																			\
																				\
	}																			\
	else																		\
	{																			\
		if (NGS_ asserts::dynamic_assert((condition), #condition, __VA_ARGS__))	\
		{																		\
			NGS_ASSERT_FAIL;													\
		}																		\
	}																			\
} while (false)																	\
//
#	endif

#else
#	define NGS_ASSERT(condition,...) ((void)0)

#	if NGS_CPP_STANDARD_HAS_20
#		define NGS_ASSERT_IF_CONSTEVAL(condition,...) ((void)0)
#	endif

#endif


