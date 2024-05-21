#pragma once

#include "./defined.h"

NGS_LIB_BEGIN
	namespace detail
{
	template<class T>
	concept valid_underlying = bits::bitsets::bit_fundamental<bits::bitsets::underlying_type_t<T>>;

	template<class T>
	concept has_member = requires(const T& t)
	{
		{ t.value() } -> ::std::convertible_to<bits::bitsets::underlying_type_t<T>>;
	};

	template<class T>
	concept has_adl = requires(const T& t)
	{
		{ value_of(t) } -> ::std::convertible_to<bits::bitsets::underlying_type_t<T>>;
	};

	template<class T>
	concept convertible = ::std::convertible_to<T, bits::bitsets::underlying_type_t<T>>;
}

inline constexpr struct
{
	constexpr decltype(auto) operator()(auto&& physical) const
		requires (detail::valid_underlying<decltype(physical)>)
	{
		if constexpr (detail::has_member<decltype(physical)>)
		{
			return physical.value();
		}
		else if constexpr (detail::has_adl<decltype(physical)>)
		{
			return value_of(physical);
		}
		else if constexpr (detail::convertible<decltype(physical)>)
		{
			return static_cast<bits::bitsets::underlying_type_t<decltype(physical)>>(physical);
		}
		else
		{
			return *reinterpret_cast<const bits::bitsets::underlying_type_t<decltype(physical)>*>(&physical);
		}
	}
}value_of{};

NGS_LIB_END