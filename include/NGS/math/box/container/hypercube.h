#pragma once

#include "../operator.h"
#include "../internal.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(vectors::index_t index, auto&& position, auto&& size)const
		{
			using position_type = vectors::value_t<decltype(position)>;
			using size_type = vectors::value_t<decltype(size)>;
			using result_type = internal<::std::common_reference_t<position_type, size_type>>;

			if constexpr (::std::unsigned_integral<size_type>)
			{
				return result_type(
					vectors::ops::access(NGS_PP_PERFECT_FORWARD(position), index),
					vectors::ops::access(NGS_PP_PERFECT_FORWARD(position), index) + vectors::ops::access(NGS_PP_PERFECT_FORWARD(size), index)
				);
			}
			else
			{
				auto&& p = vectors::ops::access(NGS_PP_PERFECT_FORWARD(position), index);
				auto&& s = vectors::ops::access(NGS_PP_PERFECT_FORWARD(size), index);
				return result_type(
					p + s * (s < 0),
					p + s * (s > 0)
				);
			}
		}
	}hypercube_transformer{};

	template<vectors::scalar _Position, vectors::scalar _Size, vectors::extent_t _Dimension>
	using basic_hypercube = vectors::views::transform_default_sentinel_view<hypercube_transformer, _Dimension, vectors::vector<_Position, _Dimension>, vectors::vector<_Size, _Dimension>>;

	template<vectors::scalar _Position, vectors::scalar _Size, vectors::extent_t _Dimension, class = ::std::make_index_sequence<_Dimension>>
	struct hypercube;

	template<vectors::scalar _Position, vectors::scalar _Size, vectors::extent_t _Dimension, size_t... _Index>
	struct hypercube<_Position, _Size, _Dimension, ::std::index_sequence<_Index...>> : basic_hypercube<_Position, _Size, _Dimension>
	{
		NGS_MPL_ENVIRON(hypercube);
	public:
		using position_type = _Position;
		using size_type = _Size;

		using position_point_type = vectors::vector<position_type, _Dimension>;
		using size_point_type = vectors::vector<size_type, _Dimension>;

		constexpr hypercube() : base_type(position_point_type(), size_point_type()) {}
		constexpr hypercube(const position_point_type& position, const size_point_type& size) : base_type(position, size) {}
		constexpr explicit hypercube(const type_traits::index_type_identity_t<_Index, position_type>&... position, const type_traits::index_type_identity_t<_Index, size_type>&... size)
			: base_type(position_point_type(position...), size_point_type(size...)) {}
		constexpr explicit hypercube(const position_point_type& position, const type_traits::index_type_identity_t<_Index, size_type>&... size) : base_type(position, size_point_type(size...)) {}
		constexpr explicit hypercube(const type_traits::index_type_identity_t<_Index, position_type>&... position, const size_point_type& size) : base_type(position_point_type(position...), size) {}

		constexpr auto&& position()const { return functional::parameter_packet::unpack<0>(base_type::get_parameter_packet()); }
		constexpr auto&& position() { return functional::parameter_packet::unpack<0>(base_type::get_parameter_packet()); }
		constexpr auto&& size()const { return functional::parameter_packet::unpack<1>(base_type::get_parameter_packet()); }
		constexpr auto&& size() { return functional::parameter_packet::unpack<1>(base_type::get_parameter_packet()); }

	};
}

template<vectors::extent_t _Dimension, vectors::scalar _Position, vectors::scalar _Size = _Position>
using hypercube = bases::adl_forward<detail::hypercube<_Position, _Size, _Dimension>, NGS_MATH_BOX_OPERATOR_NS::allow_adl_operator>;

NGS_LIB_MODULE_END