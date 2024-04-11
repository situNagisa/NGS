#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct basic_span_register
	{
		NGS_MPL_ENVIRON_BEGIN(basic_span_register);
	public:
		using underlying_type = ::std::uint64_t;

		constexpr static self_type create(underlying_type value)
		{
			return {
				.size = static_cast<std::uint16_t>(value),
				.address_low = static_cast<std::uint16_t>(value >> 16),
				.address_high = static_cast<std::uint16_t>(value >> 32)
			};
		}

		::std::uint16_t size;
		::std::uint16_t address_low;
		::std::uint16_t address_high;

		constexpr explicit(false) operator underlying_type() const noexcept
		{
			return static_cast<underlying_type>(size) | (static_cast<underlying_type>(address_low) << 16) | (static_cast<underlying_type>(address_high) << 32);
		}

		[[nodiscard]] constexpr ::std::uint32_t address() const noexcept
		{
			return static_cast<::std::uint32_t>(address_low) | (static_cast<::std::uint32_t>(address_high) << 16);
		}
	};
}

NGS_LIB_MODULE_END