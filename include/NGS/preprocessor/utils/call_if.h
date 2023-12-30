#pragma once

#define NGS_PP_CALL_IF(expression)			\
(do											\
{											\
	if constexpr (requires{ expression; })	\
	{										\
		expression;							\
	}										\
} while (false),requires{ expression; })	\
//