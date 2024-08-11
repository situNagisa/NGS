#pragma once

#include "./ack.h"
#include "./address.h"
#include "./trait.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


template<class T, class Value>
concept output_range =
::std::ranges::input_range<T>
&& ::std::ranges::sized_range<T>
&& concepts::object<Value>
&& ::std::same_as<::std::remove_cv_t<Value>, ::std::remove_cv_t<::std::ranges::range_value_t<T>>>;

template<class T, class Value>
concept input_range = ::std::ranges::output_range<T, Value>&& ::std::ranges::sized_range<T>;

namespace _details
{
	NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(write_range, (output_range<iic_value_t<T>>));
	NGS_TCEA_TRAIT_CUSTOM_POINT_OBJECT(read_range, (input_range<iic_value_t<T>>));

}

inline constexpr struct
{
	template<output_iic Target>
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(Target&& target, output_range<iic_value_t<Target>> auto&& range) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (::std::invocable<decltype(_details::write_range), Target&&,decltype(range)>)
		{
			return _details::write_range(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(range));
		}
		else
		{
			::std::size_t result = 0;
			for (auto&& value : NGS_PP_PERFECT_FORWARD(range))
			{
				if (!write(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(value)))
				{
					break;
				}
				++result;
			}
			return result;
		}
	}
}write_range{};

inline constexpr struct
{
	template<input_iic Target>
	NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()(Target&& target, input_range<iic_value_t<Target>> auto&& range) NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
	{
		if constexpr (::std::invocable<decltype(_details::read_range),Target&&,decltype(range)>)
		{
			return _details::read_range(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(range));
		}
		else
		{
			::std::size_t result = 0;
			for (auto&& value : NGS_PP_PERFECT_FORWARD(range))
			{
				if (!read(NGS_PP_PERFECT_FORWARD(target), NGS_PP_PERFECT_FORWARD(value)))
				{
					break;
				}
				++result;
			}
			return result;
		}
	}
}read_range{};

NGS_LIB_MODULE_END