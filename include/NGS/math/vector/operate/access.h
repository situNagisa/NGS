#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct access_t
	{
		constexpr decltype(auto) operator()(input_or_output_vector auto&& vector, index_t index)const
		{
			if constexpr (requires{ vector.access(index); })
			{
				return vector.access(index);
			}
			else if constexpr (requires{ access(NGS_PP_PERFECT_FORWARD(vector), index); })
			{
				return access(NGS_PP_PERFECT_FORWARD(vector), index);
			}
			else
			{
				return ::std::ranges::begin(vector)[index];
			}
		}
	};
}

inline constexpr _detail::access_t access{};

NGS_LIB_MODULE_END
