#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

namespace utility
{
	constexpr auto bit_extract(::std::unsigned_integral auto value, ::std::size_t start, ::std::size_t length)
	{
		return (value >> start) & ((1 << length) - 1);
	}

	constexpr decltype(auto) byte_extract(::std::unsigned_integral auto value, ::std::size_t start, ::std::size_t length)
	{
		return utility::bit_extract(value, bits::algorithm::byte_to_bit(start), bits::algorithm::byte_to_bit(length));
	}

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
	concept byte_representable = ::std::unsigned_integral<byte<ByteCount>>;

	constexpr decltype(auto) byte_fill() { return ::std::uint8_t{}; }

	constexpr decltype(auto) byte_fill(::std::unsigned_integral auto... value)
	{
		constexpr auto size = (sizeof(value) + ...);
		using result_type = byte<size>;

		return[=]<::std::size_t... Index>(::std::index_sequence<Index...>)
		{
			constexpr auto offsets = layout::offset(bits::algorithm::bit_of<decltype(value)>()...);

			return static_cast<result_type>(((static_cast<result_type>(value) << offsets[Index]) | ...));
		}(::std::make_index_sequence<sizeof...(value)>{});
	}
}

NGS_LIB_END