//==========================================================================================================
// @file	:	NGS/NGS_Bit
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:20:52
// @brief	:	
//==========================================================================================================
#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/template_mate.h"


NGS_BEGIN

inline constexpr uint64 bit(uint16 n) { return static_cast<uint64>(1) << n; }
inline constexpr uint64 bit_max(uint16 bitCount) { return bit(bitCount) - 1; }

template<bool B, class T>
inline void Bits(T& p, CIntegral auto bit) {
	if constexpr (B)
		p |= (T)bit;
	else
		p &= ~(T)bit;
}

inline void Bits(auto& p, CIntegral auto bit, bool boolean) {
	if (boolean)
		Bits<true>(p, bit);
	else
		Bits<false>(p, bit);
}

template<class T>
inline constexpr bool Bits(T p, CIntegral auto bit) { return p & (T)bit; }

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

static constexpr uint64 BitPerByte = 8;
#undef _N
template<uint64 _N>
	requires (_N <= (sizeof(uint64) * BitPerByte))
class BitSet {
public:
	static constexpr uint64 BitCount = _N;
	static constexpr uint64 ByteCount = (((BitCount) / BitPerByte) + (((BitCount) % BitPerByte) > 0));
	using type = byte_<ByteCount>;

	static constexpr type Mask = (BitCount == 64) ? static_cast<type>(~(uint64)0) : static_cast<type>((((uint64)1 << BitCount) - 1));


	class Bit {
		NGS_TYPE_DEFINE(BitSet<BitCount>, set);
		NGS_TYPE_DEFINE(Bit, this);

		friend class BitSet<BitCount>;
	public:
		constexpr ~Bit()noexcept {}

		__this_ref operator=(const bool boolean)noexcept {
			_set_ref._Set(_pos, boolean);
			return *this;
		}
		__this_ref operator=(__this_ref_cst other)noexcept {
			_set_ref._Set(_pos, static_cast<bool>(other));
		}
		__this_ref Flip()noexcept {
			_set_ref.Flip(_pos);
			return *this;
		}
		constexpr bool operator~()const noexcept { return !(static_cast<bool>(*this)); }
		constexpr operator bool()const noexcept { return _set_ref._Get(_pos); }

	private:
		Bit(__set_ref set_ref, size_t pos)
			: _set_ref(set_ref)
			, _pos(pos)
		{}

		__set_ref _set_ref;
		size_t _pos;
	};
	NGS_TYPE_DEFINE(Bit, bit);
	NGS_TYPE_DEFINE(BitSet<BitCount>, this);
public:
	constexpr BitSet() : _data(0) {}
	constexpr BitSet(type data) : _data(data) {}
	template<uint64 _N2>
	constexpr BitSet(const BitSet<_N2>& other)
		: BitSet(type((typename BitSet<_N2>::type)other))
	{}

	constexpr bool operator==(__this_ref_cst other)const { return _Get() == other._Get(); }

	constexpr operator type()const { return _Get(); }
	explicit(true) constexpr operator float32()const { return _Get() / ((float32)Mask); }
	explicit(true) constexpr operator float64()const { return _Get() / ((float64)Mask); }

	constexpr __bit operator[](size_t index) { return Bit(*this, index); }
	constexpr bool operator[](size_t index)const { return _Get(index); }
	constexpr bool test(size_t index)const {
		if (index < 0 || index >= (BitCount))
			throw std::out_of_range{"index out of range!"};
		return _Get(index);
	}

	__this_ref operator&=(__this_ref_cst other) { _data &= other._Get(); return *this; }
	__this_ref operator|=(__this_ref_cst other) { _data |= other._Get(); return *this; }
	__this_ref operator^=(__this_ref_cst other) { _data ^= other._Get(); return *this; }
	__this_ref operator<<=(size_t off) { _data <<= off; return *this; }
	__this_ref operator>>=(size_t off) { (_data &= Mask) >>= off; return *this; }

	constexpr __this operator&(__this_ref_cst other)const { return __this{ _data & other._Get() }; }
	constexpr __this operator|(__this_ref_cst other)const { return __this{ _data | other._Get() }; }
	constexpr __this operator^(__this_ref_cst other)const { return __this{ _data ^ other._Get() }; }
	constexpr __this operator~()const { return ~_data; }
	constexpr __this operator<<(size_t off) { return __this{ _data << off }; }
	constexpr __this operator>>(size_t off) { return __this{ _data >> off }; }

	constexpr bool All()const { return !(~_data & Mask); }
	constexpr bool Any()const { return _data & Mask; }
	constexpr bool None()const { return !Any(); }

	constexpr size_t Count()const { return std::popcount(_Get()); }

	constexpr bool IsSingleBit()const { return std::has_single_bit(_Get()); }
	constexpr type Ceil()const { return std::bit_ceil(_Get()); }
	constexpr type Floor()const { return std::bit_floor(_Get()); }
	constexpr size_t Width()const { return std::bit_width(_Get()); }

	//constexpr type RotateLeft(size_t count)const { return std::rotl(_Get(), count); }
	//constexpr type RotateRight(size_t count)const { return std::rotr(_Get(), count); }

	constexpr size_t LeadingZero()const { return std::countl_zero(_Get()) - (ByteCount * BitPerByte - BitCount); }
	constexpr size_t LeadingOne()const { return std::countl_one(_Get()); }
	constexpr size_t TrailingZero()const { return std::countr_zero(_data); }
	constexpr size_t TrailingOne()const { return std::countr_one(_data); }

	void Set() { _data = Mask; }
	void Set(type data) { _data = data; }

	void Reset() { _data = 0; }
	void Flip(size_t index) { _Set(index, !_Get(index)); }
	void Flip() { _data = ~_data; }

protected:
	void _ON(size_t index) { _data |= (1 << index); }
	void _OFF(size_t index) { _data &= ~(1 << index); }
	void _Set(size_t index, bool boolean) {
		if (boolean)
			_ON(index);
		else
			_OFF(index);
	}
	constexpr type _Get()const { return _data & Mask; }
	constexpr bool _Get(size_t index)const { return _data & (1 << index); }
private:

	type _data;
};

class Flag : public BitSet<sizeof(uint64)* BitPerByte> {
public:
	constexpr Flag()
		: BitSet<sizeof(uint64)* BitPerByte>()
	{}

	template<size_t _N>
	constexpr Flag(const BitSet<_N>& other)
		: BitSet<sizeof(uint64)* BitPerByte>(typename BitSet<_N>::type(other))
	{}

	constexpr Flag(size_t index)
		: BitSet<sizeof(uint64)* BitPerByte>(1ULL << index)
	{}

	template<CIntegral T>
	constexpr operator T()const { return _Get(); }
};

constexpr Flag FLAG_ANY = {};

#define NGS_FLAG(id,value) static constexpr _NGS Flag id{value}

NGS_END