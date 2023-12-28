#pragma once

#include "./concept.h"
#include "./tag.h"
#include "./defined.h"

NGS_LIB_BEGIN

constexpr decltype(auto) major(input_matrix auto&& matrix, index_t major)
{
	return *(::std::ranges::begin(matrix) + major);
}

constexpr decltype(auto) random_access(input_matrix auto&& matrix, index_t major_index, index_t minor_index)
{
	auto&& major_vector = NGS_LIB_NAME::major(matrix, major_index);
	return *(::std::ranges::begin(major_vector) + minor_index);
}

namespace detail
{
	template<input_matrix _M>
	struct minor_view : vectors::basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<minor_view<_M>>
	{
		using trait_type = vectors::param_trait<_M>;
		constexpr static decltype(auto) dereference(index_t major, typename trait_type::pointer matrix, index_t minor)
		{
			return NGS_LIB_NAME::random_access(*matrix, major, minor);
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

constexpr decltype(auto) minor(input_matrix auto&& matrix, index_t minor)
{
	return detail::minor_view<decltype(matrix)>(NGS_PP_PERFECT_FORWARD(matrix), minor);
}

NGS_LIB_END
