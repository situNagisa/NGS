#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<size_t _Index, class _Tuple>
	constexpr decltype(auto) get_tuple_restore(auto&& tuple)
	{
		return type_traits::restore<::std::tuple_element_t<_Index, _Tuple>>(::std::get<_Index>(NGS_PP_PERFECT_FORWARD(tuple)));
	}
	template<class _Tuple, size_t... _Index>
	constexpr decltype(auto) apply_prefix(::std::index_sequence<_Index...>, auto&& functor, auto&& tuple, auto&&... prefix_args)
	{
		return NGS_PP_PERFECT_FORWARD(functor)(NGS_PP_PERFECT_FORWARD(prefix_args)..., _detail::get_tuple_restore<_Index, _Tuple>(NGS_PP_PERFECT_FORWARD(tuple))...);
	}
}

template<extent_t _Extent, auto _Transformer, auto _Sentinel, class... _Args>
struct transform_view : basic_vector, ::std::ranges::view_base, ::std::ranges::view_interface<transform_view<_Extent, _Transformer, _Sentinel, _Args...>>
{
	using param_type = ::std::tuple<_Args...>;
	using storage_type = ::std::tuple<type_traits::storage_t<_Args>...>;

	constexpr static auto transformer = _Transformer;
	constexpr static auto sentinel = _Sentinel;

	constexpr static decltype(auto) dereference(index_t index, const storage_type* params)
	{
		static_assert(::std::invocable<decltype(transformer), index_t, _Args...>,
			"transformer must be invocable with index_t, _Args...");

		return _detail::apply_prefix<param_type>(
			::std::make_index_sequence<sizeof...(_Args)>(),
			transformer, *params, index);
	}
	using value_type = type_traits::object_t<decltype(dereference(0, nullptr))>;
	using iterator = vector_iterator<value_type, dereference, const storage_type*>;
	constexpr static auto extent = _Extent;

	constexpr explicit(false) transform_view(auto&&... args) //requires (::std::convertible_to<decltype(args), _Args> && ...)
		: _params(type_traits::store<_Args>(NGS_PP_PERFECT_FORWARD(args))...)
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
			return iterator(_detail::apply_prefix<param_type>(::std::make_index_sequence<sizeof...(_Args)>(), sentinel, _params), &_params);
		}
		else
		{
			static_assert(::std::sentinel_for<result_type, iterator>,
				"sizer must return index_t or sentinel_for<iterator>");
			return _detail::apply_prefix<param_type>(::std::make_index_sequence<sizeof...(_Args)>(), sentinel, _params);
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