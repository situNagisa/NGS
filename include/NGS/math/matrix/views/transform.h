#pragma once

#include "../concept.h"
#include "../tag.h"
#include "../operate.h"
#include "../operator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<auto _Transformer>
	struct basic_transform_view_transformer_t
	{
		constexpr decltype(auto) operator()(index_t minor, index_t major, auto&&... args)const
		{
			return _Transformer(major, minor, NGS_PP_PERFECT_FORWARD(args)...);
		}
	};

	template<auto _Transformer>
	inline constexpr basic_transform_view_transformer_t<_Transformer> basic_transform_view_transformer{};

	template<auto _Transformer, extent_t _Major, extent_t _Minor, auto _MajorSentinel, auto _MinorSentinel, class... _Args>
	using transform_view = bases::adl_forward<NGS_MATH_MATRIX_TAG_NS::retag < NGS_MATH_MATRIX_TAG_NS::matrix,
		vectors::recurse::transform_view<
		basic_transform_view_transformer<_Transformer>,
		//functional::binders::bind<sizeof...(_Args), 2>(_Transformer, functional::parameter_packet::placeholders::_2, functional::parameter_packet::placeholders::_1),
		vectors::recurse::extents<_Major, _Minor>,
		vectors::packet<_Args...>,
		_MajorSentinel, _MinorSentinel
		>>, allow_adl_operator>;
}

template<auto _Transformer, extent_t _Major, extent_t _Minor, auto _MajorSentinel, auto _MinorSentinel, class... _Args>
using transform_view = _detail::transform_view<_Transformer, _Major, _Minor, _MajorSentinel, _MinorSentinel, _Args...>;

template<auto _Transformer, extent_t _Major, extent_t _Minor, class... _Args>
using transform_default_sentinel_view = transform_view<_Transformer, _Major, _Minor,
	NGS_MATH_MATRIX_OPERATE_NS::default_major_sentinel<_Major>(),
	NGS_MATH_MATRIX_OPERATE_NS::default_minor_sentinel<_Minor>(), _Args...>;

template<auto _Transformer, input_or_output_matrix _M>
using transform_depend_view = transform_default_sentinel_view<_Transformer, major_extent_v<_M>, minor_extent_v<_M>, _M>;

template<auto _Transformer, extent_t _Major, extent_t _Minor, auto _MajorSentinel, auto _MinorSentinel, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_view< _Transformer, _Major, _Minor, _MajorSentinel, _MinorSentinel, _Args...>(NGS_PP_PERFECT_FORWARD(args)...);
}

template<auto _Transformer, extent_t _Major, extent_t _Minor, class... _Args>
constexpr auto transform(_Args&&... args)
{
	return transform_default_sentinel_view<_Transformer, _Major, _Minor, _Args...>(NGS_PP_PERFECT_FORWARD(args)...);
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
}

template<input_or_output_matrix _M, ::std::invocable<index_t, index_t, _M> _Functor>
using transform_dynamic_view = transform_default_sentinel_view<_detail::dynamic_transform, major_extent_v<_M>, minor_extent_v<_M>, _M, _Functor>;

template<input_or_output_matrix _M>
constexpr decltype(auto) transform(_M&& matrix, ::std::invocable<index_t, index_t, _M> auto&& functor)
{
	return transform_dynamic_view<_M&&, decltype(functor)>(NGS_PP_PERFECT_FORWARD(matrix), NGS_PP_PERFECT_FORWARD(functor));
}

NGS_LIB_MODULE_END