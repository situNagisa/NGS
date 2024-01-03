#pragma once


#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t major, index_t minor, auto&& vector)const
		{
			return (major == minor) * vectors::ops::access(NGS_PP_PERFECT_FORWARD(vector), major);
		}
	}basic_diagonal_matrix_transformer{};

	template<extent_t _Extent, class _T>
		requires (_Extent != adapter_extent)
	using basic_diagonal_matrix = transform_view<basic_diagonal_matrix_transformer, _Extent, _Extent,
		vectors::ops::default_sentinel<_Extent>(), vectors::ops::default_sentinel<_Extent>(),
		vectors::vector<_T, _Extent>>;

	template<extent_t _Extent, class, class = ::std::make_index_sequence<_Extent == dynamic_extent ? 1 : _Extent>>
	struct diagonal_matrix;

	template<class _T, class _S>
	struct diagonal_matrix<dynamic_extent, _T, _S> : basic_diagonal_matrix<dynamic_extent, _T>
	{
		using base_type = basic_diagonal_matrix<dynamic_extent, _T>;

		constexpr diagonal_matrix(const vectors::vector<_T, dynamic_extent>& value)
			: base_type(value)
		{}
		constexpr diagonal_matrix(const ::std::convertible_to<_T> auto&... value)
			: base_type(vectors::vector<_T, dynamic_extent>{ value... })
		{}

		using base_type::operator=;
	};

	template<extent_t _Extent, class _T, size_t... _Index>
		requires (_Extent != dynamic_extent)
	struct diagonal_matrix < _Extent, _T, ::std::index_sequence<_Index...>> : basic_diagonal_matrix<_Extent, _T>
	{
		using base_type = basic_diagonal_matrix<_Extent, _T>;

		constexpr diagonal_matrix(const type_traits::index_type_identity_t<_Index, _T>&... value)
			: base_type(vectors::vector<_T, _Extent>{ value... })
		{}

		using base_type::operator=;
	};
}

template<class _T, extent_t _Extent = dynamic_extent> requires (_Extent != adapter_extent)
using diagonal_matrix = _detail::diagonal_matrix<_Extent, _T>;


NGS_LIB_MODULE_END