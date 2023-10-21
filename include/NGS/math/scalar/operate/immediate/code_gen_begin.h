#include "../defined.h"
#include "../../impl.h"

#define NGS_MATH_SCALAR_GEN_FUNCTION(id,expression,...)					\
namespace operate_detail												\
{																		\
struct id##_function_impl												\
{																		\
	constexpr auto operator()(__VA_ARGS__)const							\
	{																	\
		if constexpr (requires{ scalar(expression); })					\
		{																\
			return scalar(expression);									\
		}																\
		else															\
		{																\
			static_assert(ccpt::None<decltype(expression)>, "can not " #id);\
		}																\
	}																	\
};																		\
inline constexpr id##_function_impl id{};								\
}																		\
using operate_detail::id												\
//

#define NGS_MATH_SCALAR_GEN_UNARY(id,op)																		\
NGS_MATH_SCALAR_GEN_FUNCTION(id,op value(NGS_PERFECT_FORWARD(expression)), CScalarExpression auto&& expression)	\
//

#define NGS_MATH_SCALAR_GEN_BINARY(id,op)																															\
NGS_MATH_SCALAR_GEN_FUNCTION(id,value(NGS_PERFECT_FORWARD(left)) op value(NGS_PERFECT_FORWARD(right)),CScalarExpression auto&& left,CScalarExpression auto&& right)	\
//
