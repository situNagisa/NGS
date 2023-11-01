#pragma once

#include "./core.h"

NGS_BASIC_TYPE_BEGIN
namespace detail
{
template<size_t _Byte>
struct _byte_
{
	using type = decltype([] {
		if		constexpr (_Byte > 4)
			return uint64();
		else if constexpr (_Byte > 2)
			return uint32();
		else if constexpr (_Byte > 1)
			return uint16();
		else
			return uint8();
		}());
};
}


template<size_t _Byte>
using byte_ = typename detail::_byte_<_Byte>::type;

NGS_BASIC_TYPE_DEFINE(byte_<0>, byte);

NGS_BASIC_TYPE_DEFINE(byte_<sizeof(void*)>, ptr_t);

NGS_BASIC_TYPE_END