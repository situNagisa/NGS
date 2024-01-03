#pragma once

#include "../concept.h"
#include "../tag.h"
#include "../size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<auto _Transformer>
	struct transform_minor_transformer
	{
		constexpr static auto transformer = _Transformer;
		constexpr decltype(auto) operator()(index_t minor, index_t major, auto&&... args)const
		{
			return transformer(major, minor, NGS_PP_PERFECT_FORWARD(args)...);
		}
	};
	template<auto _Transformer>
	inline constexpr transform_minor_transformer<_Transformer> transform_minor_transformer_v{};

	template<auto _Sizer>
	struct transform_minor_sizer
	{
		constexpr static auto sizer = _Sizer;
		constexpr decltype(auto) operator()(index_t major, auto&&... args)const
		{
			return sizer(NGS_PP_PERFECT_FORWARD(args)...);
		}
	};
	template<auto _Sizer>
	inline constexpr transform_minor_sizer<_Sizer> transform_minor_sizer_v{};

	template<extent_t _Extent, auto _Transformer, auto _Sizer, class... _Args>
	using transform_minor_view = vectors::views::transform_view < _Extent, transform_minor_transformer_v<_Transformer>, transform_minor_sizer_v<_Sizer>, index_t, _Args... >;

	template<extent_t _Extent, auto _Transformer, auto _Sizer, class... _Args>
	struct transform_major_transformer
	{
		constexpr decltype(auto) operator()(index_t major, auto&&... args)const
		{
			return transform_minor_view<_Extent, _Transformer, _Sizer, _Args...>(major, NGS_PP_PERFECT_FORWARD(args)...);
		}
	};
	template<extent_t _Extent, auto _Transformer, auto _Sizer, class... _Args>
	inline constexpr transform_major_transformer<_Extent, _Transformer, _Sizer, _Args...> transform_major_transformer_v{};

	template<extent_t _Major, extent_t _Minor, auto _Transformer, auto _MajorSizer, auto _MinorSizer, class... _Args>
	using basic_transform_view = vectors::views::transform_view < _Major,
		transform_major_transformer_v<_Minor, _Transformer, _MinorSizer, _Args...>,
		_MajorSizer, _Args... >;

	template<extent_t _Major, extent_t _Minor, auto _Transformer, auto _MajorSizer, auto _MinorSizer, class... _Args>
	struct transform_view : basic_transform_view<_Major, _Minor, _Transformer, _MajorSizer, _MinorSizer, _Args...>, basic_matrix
	{
		using base_type = basic_transform_view<_Major, _Minor, _Transformer, _MajorSizer, _MinorSizer, _Args...>;
		using basic_matrix::nmla_type;

		using base_type::base_type;
		using base_type::operator=;
	};
}

using _detail::transform_view;

template<input_or_output_matrix _M, auto _Transformer>
using depend_transform_view = transform_view<major_extent_v<_M>, minor_extent_v<_M>, _Transformer, default_major_sizer<major_extent_v<_M>>(),
	default_minor_sizer<minor_extent_v<_M>>(), _M>;

template<extent_t _Major, extent_t _Minor, auto _Transformer, auto _MajorSizer, auto MinorSizer, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_view<_Major, _Minor, _Transformer, _MajorSizer, MinorSizer, _Args...>(NGS_PP_PERFECT_FORWARD(args)...);
}

template<extent_t _Major, extent_t _Minor, auto _Transformer, class... _Args>
	requires vectors::default_sentinel_able<_Major, decltype(major_size), _Args...>&& vectors::default_sentinel_able<_Minor, decltype(minor_size), _Args...>
constexpr auto transform(_Args&&... args)
{
	return transform_view<_Major, _Minor, _Transformer, default_major_sizer<_Major>(), default_minor_sizer<_Minor>(), _Args...>(
		NGS_PP_PERFECT_FORWARD(args)...);
}

template<auto _Transformer, class... _Args>
constexpr decltype(auto) transform(_Args&&... args)
{
	return NGS_LIB_MODULE_NAME::transform<dynamic_extent, dynamic_extent, _Transformer, _Args...>(NGS_PP_PERFECT_FORWARD(args)...);
}

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t major, index_t minor, input_or_output_matrix auto&& matrix, auto&& functor)const
		{
			return NGS_PP_PERFECT_FORWARD(functor)(major, minor, NGS_PP_PERFECT_FORWARD(matrix));
		}
	}dynamic_transform{};

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(input_or_output_matrix auto&& matrix, auto&&)const
		{
			return major_size(NGS_PP_PERFECT_FORWARD(matrix));
		}
	}dynamic_transform_major_sizer{};

	inline constexpr struct
	{
		constexpr decltype(auto) operator()(input_or_output_matrix auto&& matrix, auto&&)const
		{
			return minor_size(NGS_PP_PERFECT_FORWARD(matrix));
		}
	}dynamic_transform_minor_sizer{};
}

template<input_or_output_matrix _M, ::std::invocable<index_t, index_t, _M> _Functor>
using dynamic_transform_view = transform_view<major_extent_v<_M>, minor_extent_v<_M>, _detail::dynamic_transform, _detail::dynamic_transform_major_sizer,
	_detail::dynamic_transform_minor_sizer, _M, _Functor>;

template<input_or_output_matrix _M>
constexpr decltype(auto) transform(_M&& matrix, ::std::invocable<index_t, index_t, _M> auto&& functor)
{
	return dynamic_transform_view<_M&&, decltype(functor)>(NGS_PP_PERFECT_FORWARD(matrix), NGS_PP_PERFECT_FORWARD(functor));
}

NGS_LIB_MODULE_END