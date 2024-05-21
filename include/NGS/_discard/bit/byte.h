#pragma once

#include "./bitset.h"
#include "./defined.h"

NGS_LIB_BEGIN

namespace detail
{
	template<::std::size_t ByteCount>
	struct byte
	{
		using type = decltype([] {

			if		constexpr (ByteCount > sizeof(::std::uintmax_t))
				return void();
			else if	constexpr (ByteCount > sizeof(::std::uint64_t))
				return ::std::uintmax_t();
			else if	constexpr (ByteCount > sizeof(::std::uint32_t))
				return ::std::uint64_t();
			else if constexpr (ByteCount > sizeof(::std::uint16_t))
				return ::std::uint32_t();
			else if constexpr (ByteCount > sizeof(::std::uint8_t))
				return ::std::uint16_t();
			else
				return ::std::uint8_t();
			}());
	};
}

template<::std::size_t ByteCount>
using byte = typename detail::byte<ByteCount>::type;

template<::std::size_t ByteCount>
concept byte_representable = bitsets::bit_fundamental<byte<ByteCount>>;

NGS_LIB_END