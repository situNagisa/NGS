#pragma once

#include "../extent.h"
#include "./size.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN


namespace _detail
{

	template<index_t _Index>
	struct dynamic_size_at_t
	{
		constexpr decltype(auto) operator()(input_or_output_vector auto&& vector, auto&&...)const
		{
			return size_at<_Index>(NGS_PP_PERFECT_FORWARD(vector));
		}
	};

	template<index_t _Index>
	inline constexpr dynamic_size_at_t<_Index> dynamic_size_at{};

	template<extent_t _Extent>
	struct static_extent_size_t
	{
		constexpr extent_t operator()(auto&&...)const
		{
			return _Extent;
		}
	};
	template<extent_t _Extent>
	inline constexpr static_extent_size_t<_Extent> static_extent_size{};
}

template<extent_t _Extent, auto _Dynamic = _detail::dynamic_size_at<0>, auto _Sentinel = make_adapter_sentinel>
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
		return _detail::static_extent_size<_Extent>;
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
	template<extent_t _Extent, class _DynamicSentinel, class... _Args>
	concept default_sentinel_able = (_Extent != dynamic_extent) || ::std::invocable<_DynamicSentinel, _Args...>;
}
NGS_LIB_END