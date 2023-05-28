//==========================================================================================================
// @file	:	NGS/NGS_Bit
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:20:52
// @brief	:	
//==========================================================================================================
#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_TypeTrait.h"


NGS_BEGIN

NGS_CONCEPT

template<class T>
concept Bit = _TYT IsINT<T> || requires(T a) {
	(int)a;
};

NGS_END

inline constexpr uint64 bit(uint16 n) { return static_cast<uint64>(1) << n; }
inline constexpr uint64 bit_max(uint16 bitCount) { return bit(bitCount) - 1; }

template<bool B, class T>
inline void Bits(T& p, _CPT Bit auto bit) {
	if constexpr (B)
		p |= (T)bit;
	else
		p &= ~(T)bit;
}

inline void Bits(auto& p, _CPT Bit auto bit, bool boolean) {
	if (boolean)
		Bits<true>(p, bit);
	else
		Bits<false>(p, bit);
}

template<class T>
inline constexpr bool Bits(T p, _CPT Bit auto bit) { return p & (T)bit; }

template<size_t start, size_t end>
inline void Bits(auto& dest, auto source) {
	For<start, end>([&](uint16 i) {
		bool b = Bits(source, bit(i));
		Bits(dest, bit(i), b);
		});
}


inline constexpr size_t BitsOf(auto target = 0) { return sizeof(target) * 8; }
inline constexpr size_t ByteOf(size_t bitCount) {
	constexpr auto byteBits = BitsOf<byte>();
	if (bitCount % byteBits)return bitCount / byteBits + 1;
	return bitCount / byteBits;
}

NGS_TYPE

using FLAG = byte;

NGS_END

NGS_END