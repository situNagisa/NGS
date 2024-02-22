#pragma once

#include "../operator.h"
#include "../internal.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(vectors::index_t index, auto&& min, auto&& max)const
		{
			using min_type = vectors::value_t<decltype(min)>;
			using max_type = vectors::value_t<decltype(max)>;
			return internal<::std::common_reference_t<min_type, max_type>>(vectors::ops::access(NGS_PP_PERFECT_FORWARD(min), index), vectors::ops::access(NGS_PP_PERFECT_FORWARD(max), index));
		}
	}minmax_transformer{};

	template<vectors::scalar _T, vectors::extent_t _Dimension>
	using basic_minmax = vectors::views::transform_default_sentinel_view<minmax_transformer, _Dimension, vectors::vector<_T, _Dimension>, vectors::vector<_T, _Dimension>>;

	template<vectors::scalar _T, vectors::extent_t _Dimension, class = ::std::make_index_sequence<_Dimension>>
	struct minmax;

	template<vectors::scalar _T, vectors::extent_t _Dimension, size_t... _Index>
	struct minmax<_T, _Dimension, ::std::index_sequence<_Index...>> : basic_minmax<_T, _Dimension>
	{
		NGS_MPL_ENVIRON(minmax);
		using _value_type = _T;
	public:
		using point_type = vectors::vector<_value_type, _Dimension>;

		constexpr minmax() : base_type(point_type(), point_type()) {}
		constexpr minmax(const point_type& min, const point_type& max) : base_type(min, max) {}
		constexpr explicit minmax(const type_traits::index_type_identity_t<_Index, _value_type>&... min, const type_traits::index_type_identity_t<_Index, _value_type>&... max) : base_type(point_type(min...), point_type(max...)) {}
		constexpr explicit minmax(const point_type& min, const type_traits::index_type_identity_t<_Index, _value_type>&... max) : base_type(min, point_type(max...)) {}
		constexpr explicit minmax(const type_traits::index_type_identity_t<_Index, _value_type>&... min, const point_type& max) : base_type(point_type(min...), max) {}

		constexpr auto&& min()
		{
			return functional::parameter_packet::unpack<0>(base_type::get_parameter_packet());
		}
		constexpr auto&& min()const
		{
			return functional::parameter_packet::unpack<0>(base_type::get_parameter_packet());
		}
		constexpr auto&& max()
		{
			return functional::parameter_packet::unpack<1>(base_type::get_parameter_packet());
		}
		constexpr auto&& max()const
		{
			return functional::parameter_packet::unpack<1>(base_type::get_parameter_packet());
		}
	};
}

template<vectors::scalar _Value, vectors::extent_t _Dimension>
using minmax = bases::adl_forward<detail::minmax<_Value, _Dimension>, NGS_MATH_BOX_OPERATOR_NS::allow_adl_operator>;

NGS_LIB_MODULE_END