#pragma once

#include "./size.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_BEGIN
namespace detail
{
	void major() = delete;

	struct major_t
	{
		constexpr decltype(auto) operator()(input_or_output_matrix auto&& matrix, index_t major_index)const
		{
			if constexpr (requires{ matrix.major(major_index); })
			{
				return matrix.major(major_index);
			}
			else if constexpr (requires{ major(matrix); })
			{
				return major(matrix, major_index);
			}
			else
			{
				return *(::std::ranges::begin(matrix) + major_index);
			}
		}
	};
}

inline constexpr detail::major_t major{};

namespace detail
{
	void random_access() = delete;

	struct random_access_t
	{
		constexpr decltype(auto) operator()(input_or_output_matrix auto&& matrix, index_t major_index, index_t minor_index)const
		{
			if constexpr (requires{ matrix.random_access(major_index, minor_index); })
			{
				return matrix.random_access(major_index, minor_index);
			}
			else if constexpr (requires{ random_access(matrix, major_index, minor_index); })
			{
				return random_access(matrix, major_index, minor_index);
			}
			else
			{
				auto&& major_vector = NGS_LIB_NAME::major(matrix, major_index);
				return *(::std::ranges::begin(major_vector) + minor_index);
			}
		}
	};
}

inline constexpr detail::random_access_t random_access{};

namespace detail
{
	void minor() = delete;

	struct minor_transformer
	{
		constexpr minor_transformer(index_t minor_index) : minor_index(minor_index) {}

		constexpr decltype(auto) operator()(index_t major_index, input_or_output_matrix auto&& matrix)const
		{
			return NGS_LIB_NAME::random_access(matrix, major_index, minor_index);
		}

		index_t minor_index{};
	};

	template<input_or_output_matrix _M>
	using minor_view = vectors::views::dynamic_transform_view<_M, minor_transformer>;

	struct minor_t
	{
		template<input_or_output_matrix _M>
		constexpr decltype(auto) operator()(_M&& matrix, index_t minor_index)const
		{
			if constexpr (requires{ matrix.minor(minor_index); })
			{
				return matrix.minor(minor_index);
			}
			else if constexpr (requires{ minor(matrix, minor_index); })
			{
				return minor(matrix, minor_index);
			}
			else
			{
				return minor_view<_M&&>(NGS_PP_PERFECT_FORWARD(matrix), minor_transformer(minor_index));
			}
		}
	};
}

inline constexpr detail::minor_t minor{};

NGS_LIB_END
