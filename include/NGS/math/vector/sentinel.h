#pragma once

#include "../extent.h"
#include "./size.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN


namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(index_t, auto&&... args)
		{
			return (*this)(NGS_PP_PERFECT_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(input_or_output_vector auto&& vector, auto&&...)
		{
			return ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vector));
		}
	}dynamic_size{};

	template<index_t _Index>
	struct dynamic_size_at_t
	{
		constexpr decltype(auto) operator()(index_t, auto&&... args)
		{
			return (*this)(NGS_PP_PERFECT_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(input_or_output_vector auto&& vector, auto&&...)
		{
			return size_at<_Index>(NGS_PP_PERFECT_FORWARD(vector));
		}
	};

	template<index_t _Index>
	inline constexpr dynamic_size_at_t<_Index> dynamic_size_at{};
}

template<extent_t _Extent, auto _Dynamic = _detail::dynamic_size, auto _Sentinel = make_adapter_sentinel>
constexpr auto default_sentinel()
{
	if constexpr (_Extent == dynamic_extent)
	{
		return _Dynamic;
	}
	else if constexpr (_Extent == adapter_extent)
	{
		return _Sentinel;
	}
	else
	{
		return [](auto&&...) {return _Extent; };
	}
}

template<index_t _Index, extent_t _Extent, auto _Dynamic = _detail::dynamic_size_at<_Index>, auto _Sentinel = make_adapter_sentinel>
constexpr auto default_sentinel_at()
{
	if constexpr (_Extent == dynamic_extent)
	{
		return _Dynamic;
	}
	else
	{
		return default_sentinel<_Extent, _Dynamic, _Sentinel>();
	}
}

NGS_LIB_MODULE_END
NGS_LIB_BEGIN
namespace NGS_MATH_VECTOR_CPT_NS
{
	template<extent_t _Extent, class _DynamicSizer, class... _Args>
	concept default_sentinel_able = (_Extent != dynamic_extent) || ::std::invocable<_DynamicSizer, _Args...>;
}
NGS_LIB_END