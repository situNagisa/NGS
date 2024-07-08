#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enumerated T, ::std::underlying_type_t<T> N = 0>
consteval auto contiguous_size()
{
	if constexpr (named_field<static_cast<T>(N)>)
	{
		return contiguous_size<T, N + 1>();
	}
	else
	{
		return N;
	}
}

namespace _detail
{
	template<class T, ::std::size_t N>
	constexpr auto push_back_array(const ::std::array<T,N>& range, auto&& value)
	{
		::std::array<T, N + 1> result{};
		auto out = ::std::ranges::copy(range, ::std::ranges::begin(result)).out;
		*out = value;
		return result;
	}

	template<::std::ranges::input_range auto Enum, ::std::size_t I>
		requires enumerated<::std::ranges::range_value_t<decltype(Enum)>>
	constexpr auto named_filter(const ::std::array<::std::ranges::range_value_t<decltype(Enum)>, I>& result)
	{
		constexpr auto iterator = ::std::ranges::next(::std::ranges::begin(Enum), I);
		if constexpr (iterator == ::std::ranges::end(Enum))
		{
			return result;
		}
		else
		{
			if constexpr (named_field<*iterator>)
			{
				return _detail::named_filter<Enum, I + 1>(_detail::push_back_array(result, *iterator));
			}
			else
			{
				return _detail::named_filter<Enum, I + 1>(result);
			}
		}
	}
}

template<::std::ranges::input_range auto Enum>
	requires enumerated<::std::ranges::range_value_t<decltype(Enum)>>
constexpr auto named_filter()
{
	return _detail::named_filter<Enum, 0>({});
}

template<enumerated T, auto... Fields>
	requires requires { ::std::array{ static_cast<T>(Fields)... }; }
constexpr auto named_filter()
{
	return NGS_LIB_MODULE_NAME::named_filter < ::std::array{ static_cast<T>(Fields)... } > ();
}

template<::std::ranges::input_range auto Enum>
	requires enumerated<::std::ranges::range_value_t<decltype(Enum)>>
constexpr auto to_names()
{
	constexpr auto enums = NGS_LIB_MODULE_NAME::named_filter<Enum>();
	return []<::std::size_t... Index>(::std::index_sequence<Index...>)
	{
		::std::array<::std::string_view, enums.size()> result{};
		((result[Index] = NGS_LIB_MODULE_NAME::enum_name<enums[Index]>()), ...);
		return result;
	}(::std::make_index_sequence<enums.size()>());
}

template<enumerated T, ::std::underlying_type_t<T> N = 0>
constexpr auto contiguous_names()
{
	constexpr auto enums = []
		{
			constexpr auto size = NGS_LIB_MODULE_NAME::contiguous_size<T, N>();
			constexpr auto indices = ::std::views::iota(0) | ::std::views::take(size) | ::std::views::transform([](auto&& v) { return static_cast<T>(v); });
			auto result = ::std::array<T, size>{};
			::std::ranges::copy(indices, ::std::ranges::begin(result));
			return result;
		}();
	return NGS_LIB_MODULE_NAME::to_names<enums>();
}

NGS_LIB_MODULE_END