#pragma once

#include "../../utility.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace segment_types
{
	struct data
	{
		bool accessed;
		bool writable;
		bool expand_down;
	};

	constexpr ::std::uint8_t segment_type_code(const data& value)
	{
		return static_cast<::std::uint8_t>(0b0000) | (value.accessed << 0) | (value.writable << 1) | (value.expand_down << 2);
	}

	struct code
	{
		bool accessed;
		bool readable;
		bool conforming;
	};

	constexpr ::std::uint8_t segment_type_code(const code& value)
	{
		return static_cast<::std::uint8_t>(0b1000) | (value.accessed << 0) | (value.readable << 1) | (value.conforming << 2);
	};

	struct local_descriptor_table
	{
		
	};

	constexpr ::std::uint8_t segment_type_code(const local_descriptor_table& value)
	{
		return static_cast<::std::uint8_t>(0b0010);
	}

	struct task_state
	{
		bool busy;
		enums::bit_width bit_width;
	};

	constexpr ::std::uint8_t segment_type_code(const task_state& value)
	{
		return static_cast<::std::uint8_t>(0b0001) | (value.busy << 1) | (static_cast<bool>(value.bit_width) << 3);
	}

	struct gate
	{
		enums::gate category;
		enums::bit_width bit_width;
	};

	constexpr ::std::uint8_t segment_type_code(const gate& value)
	{
		return static_cast<::std::uint8_t>(0b0100) | (static_cast<::std::uint8_t>(value.category) << 0) | (static_cast<bool>(value.bit_width) << 3);
	}

	template<class T>
	consteval auto descriptor_type()
	{
		using naked_type = type_traits::naked_t<T>;
		if constexpr (::std::same_as<naked_type, data> || ::std::same_as<naked_type, code>)
			return enums::segment_descriptor_type::code_or_data;
		else
			return enums::segment_descriptor_type::system;
	}
}

struct segment_descriptor
{
	NGS_PP_INJECT_BEGIN(segment_descriptor);
public:
	using underlying_type = ::std::uint64_t;

	underlying_type _limit_low : 16;
	underlying_type _base_low : 16;
	underlying_type _base_middle : 8;
	underlying_type _segment_type : 4;
	underlying_type _descriptor_type : 1;
	underlying_type _descriptor_privilege : 2;
	underlying_type _present : 1;
	underlying_type _limit_high : 4;
	underlying_type _available : 1;
	underlying_type _code_bit : 1;
	underlying_type _operation_size : 1;
	underlying_type _granularity : 1;
	underlying_type _base_high : 8;

	constexpr segment_descriptor() = default;

	constexpr segment_descriptor(
		::std::uintptr_t base,
		::std::size_t limit,
		underlying_type segment_type,
		enums::segment_descriptor_type descriptor_type,
		enums::privilege descriptor_privilege,
		bool present,
		underlying_type available,
		enums::code_bit code_bit,
		enums::bit_width operation_size,
		enums::granularity granularity
	)
		: _limit_low(static_cast<underlying_type>(utility::bit_extract(limit,0,16)))
		, _base_low(static_cast<underlying_type>(utility::bit_extract(base,0,16)))
		, _base_middle(static_cast<underlying_type>(utility::bit_extract(base,16,8)))
		, _segment_type(static_cast<underlying_type>(segment_type))
		, _descriptor_type(static_cast<underlying_type>(descriptor_type))
		, _descriptor_privilege(static_cast<underlying_type>(descriptor_privilege))
		, _present(static_cast<underlying_type>(present))
		, _limit_high(static_cast<underlying_type>(utility::bit_extract(limit,16,4)))
		, _available(available)
		, _code_bit(static_cast<underlying_type>(code_bit))
		, _operation_size(static_cast<underlying_type>(operation_size))
		, _granularity(static_cast<underlying_type>(granularity))
		, _base_high(static_cast<underlying_type>(utility::bit_extract(base,24,8)))
	{}

	constexpr segment_descriptor(
		::std::uintptr_t base,
		::std::size_t limit,
		const auto& segment_type,
		enums::privilege descriptor_privilege,
		bool present,
		underlying_type available,
		enums::code_bit code_bit,
		enums::bit_width operation_size,
		enums::granularity granularity
	)
		: self_type(
			base,
			limit,
			segment_types::segment_type_code(segment_type),
			segment_types::descriptor_type<decltype(segment_type)>(),
			descriptor_privilege,
			present,
			available,
			code_bit,
			operation_size,
			granularity
		)
	{}

	constexpr ::std::uintptr_t base() const noexcept
	{
		//return bits::algorithm::fill(static_cast<::std::uint16_t>(_base_low), static_cast<::std::uint8_t>(_base_middle), static_cast<::std::uint8_t>(_base_high));
		return
			(static_cast<::std::uintptr_t>(_base_low) << 0) |
			(static_cast<::std::uintptr_t>(_base_middle) << 16) |
			(static_cast<::std::uintptr_t>(_base_high) << 24);
	}
	constexpr ::std::size_t limit() const noexcept
	{
		//return bits::algorithm::fill(static_cast<::std::uint16_t>(_limit_low), static_cast<::std::uint8_t>(_limit_high));
		return
			(static_cast<::std::size_t>(_limit_low) << 0) |
			(static_cast<::std::size_t>(_limit_high) << 16);
	}
	constexpr auto segment_type() const noexcept { return static_cast<enums::segment_descriptor_type>(_segment_type); }
	constexpr auto descriptor_privilege() const noexcept { return static_cast<enums::privilege>(_descriptor_privilege); }
	constexpr bool present() const noexcept { return _present; }
	constexpr auto available() const noexcept { return _available; }
	constexpr auto code_bit() const noexcept { return static_cast<enums::code_bit>(_code_bit); }
	constexpr auto operation_size() const noexcept { return static_cast<enums::bit_width>(_operation_size); }
	constexpr auto granularity() const noexcept { return static_cast<enums::granularity>(_granularity); }

	constexpr auto size() const noexcept { return limit() * enums::factor(granularity()); }
	constexpr auto span() const noexcept
	{
		auto address = ::std::bit_cast<::std::byte*>(base());
		return ::std::span(address, size());
	}
};

NGS_LIB_MODULE_END