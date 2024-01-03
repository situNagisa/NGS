#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
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
				return vectors::ops::access(NGS_PP_PERFECT_FORWARD(matrix), major_index);
			}
		}
	};
}

constexpr decltype(auto) random_access(input_matrix auto&& matrix, index_t major_index, index_t minor_index)
{
	auto&& major_vector = NGS_LIB_NAME::major(matrix, major_index);
	return *(::std::ranges::begin(major_vector) + minor_index);
}

namespace detail
{
	void access();

	struct access_t
	{
		using trait_type = vectors::param_trait<_M>;
		constexpr static decltype(auto) dereference(index_t major, typename trait_type::pointer matrix, index_t minor)
		{
			if constexpr (requires{ matrix.access(major_index, minor_index); })
			{
				return matrix.access(major_index, minor_index);
			}
			else if constexpr (requires{ access(matrix, major_index, minor_index); })
			{
				return access(matrix, major_index, minor_index);
			}
			else
			{
				return vectors::recurse::access(NGS_PP_PERFECT_FORWARD(matrix), major_index, minor_index);
			}
		}
		using value_type = type_traits::object_t<decltype(dereference(0, nullptr, 0))>;
		using iterator = vectors::vector_iterator<value_type, dereference, typename trait_type::pointer, index_t>;
		constexpr static auto extent = extent_v<typename trait_type::type>;

		constexpr explicit(false) minor_view(typename trait_type::param matrix, index_t minor)
			: _matrix(&matrix)
			, _minor(minor)
		{}
		constexpr minor_view(const minor_view&) = default;

		constexpr auto begin()const { return iterator(0, _matrix, _minor); }
		constexpr auto end()const { return iterator(::std::ranges::size(*_matrix), _matrix, _minor); }

		NGS_EXTERN_STL_RANGE_INPUT_ITERATOR();

	public:
		typename trait_type::pointer _matrix;
		index_t _minor;
	};
}

inline constexpr detail::access_t access{};

namespace detail
{
	void minor() = delete;

	struct minor_transformer
	{
		constexpr minor_transformer(index_t minor_index) : minor_index(minor_index) {}

		constexpr decltype(auto) operator()(index_t major_index, input_or_output_matrix auto&& matrix)const
		{
			return NGS_LIB_NAME::NGS_MATH_MATRIX_OPERATE_NS::access(matrix, major_index, minor_index);
		}

		index_t minor_index{};
	};

	template<input_or_output_matrix _M>
	using minor_view = vectors::views::transform_dynamic_view<_M, minor_transformer>;

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

NGS_LIB_MODULE_END
