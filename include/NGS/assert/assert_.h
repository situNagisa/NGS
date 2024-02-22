#pragma once

#include "./format.h"

NGS_LIB_BEGIN

inline bool dynamic_assert(
	bool condition,
	std::string_view expression,
	std::string_view message = "",
	const locations::source_location& location = locations::source_location::current()
)
{
	if (condition)
		return true;

	print_assert(assert_format(expression, message, location));
	return false;
}

template<bool _Condition, statics::strings::string _Message = "", locations::source_location_info _Location = locations::source_location::current()>
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

NGS_LIB_END

#if NGS_COMPILER_IS_MSVC && NGS_BUILD_TYPE_IS_DEBUG
#	define NGS_ASSERT_FAIL __debugbreak()
#else
#	define NGS_ASSERT_FAIL std::abort()
#endif

#if NGS_BUILD_TYPE_IS_DEBUG

#define NGS_EXPECT(condition,...)	NGS_ asserts::dynamic_assert((condition),#condition NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__))

#define NGS_ASSERT(condition,...)									\
do																	\
{																	\
	if (!NGS_EXPECT(condition ,__VA_ARGS__))						\
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
		if (!NGS_EXPECT(condition ,__VA_ARGS__))								\
		{																		\
			NGS_ASSERT_FAIL;													\
		}																		\
	}																			\
} while (false)																	\
//
#	endif

#else

#	define NGS_EXPECT(condition,...) false
#	define NGS_ASSERT(condition,...) ((void)0)

#	if NGS_CPP_STANDARD_HAS_20
#		define NGS_ASSERT_IF_CONSTEVAL(condition,...) ((void)0)
#	endif

#endif

#define NGS_ASSERT_IF_CONSTEXPR(condition,...) static_assert(condition NGS_PP_VA_ARGS_OPT_COMMA(__VA_ARGS__)); if constexpr(condition)


