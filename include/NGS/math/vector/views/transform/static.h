#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<size_t... _Index>
	constexpr decltype(auto) apply(::std::index_sequence<_Index...>, auto&& functor, auto&& packer)
	{
		return NGS_PP_PERFECT_FORWARD(functor)(functional::parameter_packet::unpack<_Index>(NGS_PP_PERFECT_FORWARD(packer))...);
	}
}

template<extent_t _Extent, auto _Transformer, auto _Sentinel, class... _Args>
struct transform_view : basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<transform_view<_Extent, _Transformer, _Sentinel, _Args...>>
{
	using storage_type = functional::parameter_packet::packet<_Args...>;

	constexpr static auto transformer = _Transformer;
	constexpr static auto sentinel = _Sentinel;

	constexpr static /*::std::invoke_result_t<decltype(transformer), index_t, _Args...>*/decltype(auto) dereference(index_t index, const storage_type* params)
	{
		static_assert(::std::invocable<decltype(transformer), index_t, _Args...>,
			"transformer must be invocable with index_t, _Args...");

		return _detail::apply(::std::make_index_sequence<sizeof...(_Args)>(), functional::binders::bind<sizeof...(_Args)>(transformer, index), *params);
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

public:
	storage_type _params;
};

template<extent_t _Extent, auto _Transformer, auto _Sizer, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_view<_Extent, _Transformer, _Sizer, _Args...>(NGS_PP_PERFECT_FORWARD(args)...);
}

template<extent_t _Extent, auto _Transformer, class... _Args> requires default_sentinel_able<_Extent, decltype(::std::ranges::size), _Args...>
constexpr auto transform(_Args&&... args)
{
	return transform_view < _Extent, _Transformer, NGS_MATH_VECTOR_OPERATE_NS::default_sentinel<_Extent>(), _Args... >(NGS_PP_PERFECT_FORWARD(args)...);
}

template<input_or_output_vector _V, auto _Transformer>
using transform_depend_view = transform_view<extent_v<_V>, _Transformer, NGS_MATH_VECTOR_OPERATE_NS::default_sentinel<extent_v<_V>>(), _V>;

NGS_LIB_MODULE_END