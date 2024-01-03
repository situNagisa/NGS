#pragma once

#include "../concept.h"
#include "../operate.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<extent_t... _Extents>
struct extents : ccpt::constant_<size_t, sizeof...(_Extents)> {};

namespace _detail
{
	template<auto _Sentinel, size_t _Depth, class = ::std::make_index_sequence<_Depth>>
	struct transform_view_sentinel_t;

	template<auto _Sentinel, size_t _Depth, size_t... _Index>
	struct transform_view_sentinel_t<_Sentinel, _Depth, ::std::index_sequence<_Index...>>
	{
		constexpr decltype(auto) operator()(type_traits::index_type_identity_t<_Index, index_t>..., auto&&... args)const
		{
			return _Sentinel(NGS_PP_PERFECT_FORWARD(args)...);
		}
	};
	template<auto _Sentinel, size_t _Depth>
	inline constexpr transform_view_sentinel_t<_Sentinel, _Depth> transform_view_sentinel{};

	template<index_t _Index, auto _Transformer, class _Extents, class _Args, auto... _Sentinels>
	struct transform_view;

	template<index_t _Index, auto _Transformer, class _Extents, class _Args, auto... _Sentinels>
	using transform_view_t = typename transform_view<_Index, _Transformer, _Extents, _Args, _Sentinels...>::type;

	template<
		index_t _Index,
		auto _Transformer,
		extent_t _Extent, extent_t... _Extents,
		template<class...>class _ArgContainer, class... _Args,
		auto _Sentinel, auto... _Sentinels
	> requires (sizeof...(_Extents) == sizeof...(_Sentinels))
		struct transform_view<_Index, _Transformer, extents<_Extent, _Extents...>, _ArgContainer<_Args...>, _Sentinel, _Sentinels...>
	{
		constexpr static struct {
			constexpr decltype(auto) operator()(index_t index, auto&&... args)const {

				if constexpr (sizeof...(_Extents))
				{
					return transform_view_t<_Index + 1, _Transformer, extents<_Extents...>, _ArgContainer<index_t, _Args...>, _Sentinels...>(index, NGS_PP_PERFECT_FORWARD(args)...);
				}
				else
				{
					return _Transformer(index, NGS_PP_PERFECT_FORWARD(args)...);
				}
			}
		}transformer{};

		constexpr static auto get_type()
		{
			using result_type = views::transform_view<
				transformer,
				_Extent,
				_ArgContainer<_Args...>,
				transform_view_sentinel<_Sentinel, _Index>
				//functional::binders::bind<sizeof...(_Args) - _Index, _Index>(_Sentinel)
			>;

			return declval<result_type>();
		}

		using type = decltype(get_type());
	};
}

template<auto _Transformer, class _Extents, functional::parameter_packet::packet_like _Args, auto... _Sentinels>
using transform_view = _detail::transform_view_t<0, _Transformer, _Extents, _Args, _Sentinels...>;

namespace _detail
{
	template<auto, class _Extents, class, class = ::std::make_index_sequence<_Extents::value>>
	struct transform_default_sentinel_view;

	template<auto _Transformer, extent_t... _Extents, class _Args, size_t... _Index>
	struct transform_default_sentinel_view<_Transformer, extents<_Extents...>, _Args, ::std::index_sequence<_Index...>>
	{
		using type = NGS_LIB_MODULE_NAME::transform_view < _Transformer, extents<_Extents...>, _Args,
			NGS_MATH_VECTOR_OPERATE_NS::default_sentinel_at<_Index, _Extents>()...
		>;
	};
}
template<auto _Transformer, class _Extents, functional::parameter_packet::packet_like _Args>
using transform_default_sentinel_view = typename _detail::transform_default_sentinel_view<_Transformer, _Extents, _Args>::type;

namespace _detail
{
	template<auto _Transformer, class _V, class = ::std::make_index_sequence<depth_v<_V>>>
	struct transform_depend_view;

	template<auto _Transformer, class _V, size_t... _Index>
	struct transform_depend_view<_Transformer, _V, ::std::index_sequence<_Index...>>
	{
		using type = NGS_LIB_MODULE_NAME::transform_default_sentinel_view<_Transformer, extents<extent_at_v<_V, _Index>...>, packet<_V>>;
	};
}

template<auto _Transformer, input_or_output_vector _V>
using transform_depend_view = typename _detail::transform_depend_view<_Transformer, _V>::type;

NGS_LIB_MODULE_END