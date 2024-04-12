#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct gate_descriptor
{
	NGS_MPL_ENVIRON_BEGIN(gate_descriptor);
public:
	using underlying_type = ::std::uint64_t;

	enum class gate_type : underlying_type
	{
		task = 0b0101,
		trap_16 = 0b0110,
		trap_32 = 0b1110,
		interrupt_16 = 0b0111,
		interrupt_32 = 0b1111,
	};

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.offset_low = static_cast<underlying_type>((value >> 0) & 0xffff)
				, .cs = static_cast<underlying_type>((value >> 16) & 0xffff)
				, .param = static_cast<underlying_type>((value >> 32) & 0x1f)
				, .zero = static_cast<underlying_type>((value >> 37) & 0x7)
				, .type = static_cast<enum gate_type>((value >> 40) & 0xf)
				, .s = static_cast<underlying_type>((value >> 44) & 0x1)
				, .dpl = static_cast<underlying_type>((value >> 45) & 0x3)
				, .p = static_cast<underlying_type>((value >> 47) & 0x1)
				, .offset_high = static_cast<underlying_type>((value >> 48) & 0xffff)
			};
		}
		else
		{
			return *reinterpret_cast<self_type const*>(&value);
		}
	}

	constexpr explicit(false) operator underlying_type() const
	{
		if (::std::is_constant_evaluated())
		{
			return
				(static_cast<underlying_type>(offset_low) & 0xffff) << 0
				| (static_cast<underlying_type>(cs) & 0xffff) << 16
				| (static_cast<underlying_type>(param) & 0x1f) << 32
				| (static_cast<underlying_type>(zero) & 0x7) << 37
				| (static_cast<underlying_type>(type) & 0xf) << 40
				| (static_cast<underlying_type>(s) & 0x1) << 44
				| (static_cast<underlying_type>(dpl) & 0x3) << 45
				| (static_cast<underlying_type>(p) & 0x1) << 47
				| (static_cast<underlying_type>(offset_high) & 0xffff) << 48
				;
		}
		else
		{
			return *reinterpret_cast<underlying_type const*>(this);
		}
	}

	underlying_type
		offset_low : 16
		, cs : 16
		, param : 5
		, zero : 3
		;
	gate_type type : 4;
	underlying_type
		s : 1
		, dpl : 2
		, p : 1
		, offset_high : 16
		;

	[[nodiscard]] constexpr ::std::uint32_t offset()const { return static_cast<::std::uint32_t>(offset_low) | (static_cast<::std::uint32_t>(offset_high) << 16); }
	[[nodiscard]] constexpr ::std::uint16_t selector()const { return static_cast<::std::uint16_t>(cs); }
	[[nodiscard]] constexpr auto parameter()const { return static_cast<::std::uint8_t>(param); }
	[[nodiscard]] constexpr auto gate_type()const { return type; }
	[[nodiscard]] constexpr auto privilege()const { return static_cast<::std::uint8_t>(dpl); }
	[[nodiscard]] constexpr bool present()const { return static_cast<::std::uint8_t>(p); }

};

NGS_LIB_MODULE_END