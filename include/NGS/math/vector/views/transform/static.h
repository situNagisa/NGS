#pragma once

#include "./defined.h"

NGS_LIB_BEGIN
using functional::parameter_packet::packet;
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

template<auto _Transformer, extent_t _Extent, functional::parameter_packet::packet_like _Args, auto _Sentinel>
struct transform_view;

template<auto _Transformer, extent_t _Extent, template<class...>class _ArgContainer, class... _Args, auto _Sentinel>
struct transform_view<_Transformer, _Extent, _ArgContainer<_Args...>, _Sentinel>
	: allow_adl_operator, allow_adl_io
	, NGS_MATH_VECTOR_TAG_NS::tag<NGS_MATH_VECTOR_TAG_NS::vector>
	, ::std::ranges::view_base
	, ::std::ranges::view_interface<transform_view<_Transformer, _Extent, _ArgContainer<_Args...>, _Sentinel>>
{
	NGS_MPL_ENVIRON_BEGIN(transform_view);
public:
	using storage_type = _ArgContainer<_Args...>;

	constexpr static auto transformer = _Transformer;
	constexpr static auto sentinel = _Sentinel;

	constexpr static decltype(auto) dereference(index_t index, const storage_type* params)
	{
		static_assert(::std::invocable<decltype(transformer), index_t, _Args...>,
			"transformer must be invocable with index_t, _Args...");

		return functional::parameter_packet::apply_pair(transformer, functional::parameter_packet::make_packet(index), *params);
	}
	using value_type = type_traits::object_t<decltype(dereference(0, nullptr))>;
	using iterator = vector_iterator<value_type, dereference, const storage_type*>;
	constexpr static auto extent = _Extent;

	constexpr explicit(false) transform_view(auto&&... args) //requires (::std::convertible_to<decltype(args), _Args> && ...)
		: _params(NGS_PP_PERFECT_FORWARD(args)...)
	{}

	constexpr auto begin()const { return iterator(0, &_params); }
	constexpr auto end()const
	{
		using sizer_type = decltype(sentinel);
		static_assert(::std::invocable<sizer_type, _Args...>,
			"sizer must be invocable with param_type");
		using result_type = ::std::invoke_result_t<sizer_type, _Args...>;
		if constexpr (::std::convertible_to<result_type, index_t>)
		{
			return iterator(functional::parameter_packet::apply(sentinel, _params), &_params);
		}
		else
		{
			static_assert(::std::sentinel_for<result_type, iterator>,
				"sizer must return index_t or sentinel_for<iterator>");
			return functional::parameter_packet::apply(sentinel, _params);
		}
	}

	constexpr auto&& get_parameter_packet() { return _params; }
	constexpr auto&& get_parameter_packet()const { return _params; }
public:
	storage_type _params;
};

template<auto _Transformer, extent_t _Extent, class... _Args>
using transform_default_sentinel_view = transform_view<_Transformer, _Extent, packet<_Args...>, NGS_MATH_VECTOR_OPERATE_NS::default_sentinel<_Extent>()>;

template<auto _Transformer, extent_t _Extent, auto _Sentinel, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_view<_Transformer, _Extent, packet<_Args...>, _Sentinel>(NGS_PP_PERFECT_FORWARD(args)...);
}

template<auto _Transformer, extent_t _Extent, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_view < _Transformer, _Extent, packet<_Args...>, NGS_MATH_VECTOR_OPERATE_NS::default_sentinel<_Extent>() >(NGS_PP_PERFECT_FORWARD(args)...);
}

template<auto _Transformer, input_or_output_vector _V>
using transform_depend_view = transform_default_sentinel_view<_Transformer, extent_v<_V>, _V>;

NGS_LIB_MODULE_END