//==========================================================================================================
// @file	:	NGS/NGS_Bit
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:20:52
// @brief	:	
//==========================================================================================================
#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/concepts.h"

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4293)
#endif

NGS_BEGIN

namespace bit {

constexpr size_t bit_per_byte = 8;

template<CUnsignedIntegral _Int> constexpr _Int scope(size_t index) { return (_Int)1 << index; }
constexpr uint64 scope(size_t index) { return scope<uint64>(index); }

constexpr size_t as_byte(size_t bit_count) { return (((bit_count) / bit_per_byte) + (((bit_count) % bit_per_byte) > 0)); }
constexpr size_t as_bit(size_t byte_count) { return byte_count * bit_per_byte; }
template<class  T> consteval size_t as_bit() { return as_bit(sizeof(T)); }

//template<CUnsignedIntegral _Int> constexpr _Int mask(CUnsignedIntegral auto bit_count) { return (bit_count >= as_bit<_Int>()) ? (_Int)(-1) : (scope<_Int>(bit_count) - 1); }
constexpr uint64 mask(CIntegral auto bit_count) { return (bit_count >= as_bit<uint64>()) ? (uint64)(-1) : (scope<uint64>(bit_count) - 1); }

constexpr auto set(auto bit_set, auto bit_scope, bool state) { return state ? bit_set | bit_scope : bit_set & ~bit_scope; }
constexpr auto get(auto bit_set, auto bit_scope) { return bit_set & bit_scope; }

}



#undef _N
template<uint64 _N>
	requires (_N <= bit::as_bit<uint64>())
class NGS_API  BitSet {
public:
	static constexpr uint64 BitCount = _N;
	static constexpr uint64 ByteCount = bit::as_byte(BitCount);
	using type = byte_<ByteCount>;

	static constexpr type Mask = static_cast<type>(bit::mask(BitCount));


	class  Bit {
		NGS_TYPE_DEFINE(BitSet<BitCount>, set);
		NGS_TYPE_DEFINE(Bit, this);

		friend class  BitSet<BitCount>;
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
		: BitSet(type(static_cast<typename BitSet<_N2>::type>(other)))
	{}

	constexpr bool operator==(__this_ref_cst other)const { return _Get() == other._Get(); }

	constexpr operator type()const { return _Get(); }
	explicit(true) constexpr operator float32()const { return _Get() / static_cast<float32>(Mask); }
	explicit(true) constexpr operator float64()const { return _Get() / static_cast<float64>(Mask); }

	constexpr __bit operator[](size_t index) { return Bit(*this, index); }
	constexpr bool operator[](size_t index)const { return _Get(index); }
	constexpr bool test(size_t index)const {
		if (index < 0 || index >= (BitCount))
			throw std::out_of_range{ "index out of range!" };
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

	constexpr size_t LeadingZero()const { return std::countl_zero(_Get()) - (bit::as_bit(ByteCount) - BitCount); }
	constexpr size_t LeadingOne()const { return std::countl_one(_Get()); }
	constexpr size_t TrailingZero()const { return std::countr_zero(_data); }
	constexpr size_t TrailingOne()const { return std::countr_one(_data); }

	void Set() { _data = Mask; }
	void Set(type data) { _data = data; }

	void Reset() { _data = 0; }
	void Flip(size_t index) { _Set(index, !_Get(index)); }
	void Flip() { _data = ~_data; }

protected:
	void _ON(size_t index) { _data = bit::set(_data, bit::scope(index), true); }
	void _OFF(size_t index) { _data = bit::set(_data, bit::scope(index), false); }
	void _Set(size_t index, bool boolean) { _data = static_cast<type>(bit::set(_data, bit::scope(index), boolean)); }

	constexpr type _Get()const { return _data & Mask; }
	constexpr bool _Get(size_t index)const { return bit::get(_data, bit::scope(index)); }
private:

	type _data;
};

class NGS_API  Flag : public BitSet<bit::as_bit<uint64>()> {
public:
	constexpr Flag()
		: BitSet<bit::as_bit<uint64>()>()
	{}

	template<size_t _N>
	constexpr Flag(const BitSet<_N>& other)
		: BitSet<bit::as_bit<uint64>()>(typename BitSet<_N>::type(other))
	{}

	constexpr Flag(size_t index)
		: BitSet<bit::as_bit<uint64>()>(1ULL << index)
	{}

	template<CIntegral T>
	constexpr operator T()const { return _Get(); }
};

constexpr Flag FLAG_ANY = {};

#define NGS_FLAG(id,value) static constexpr _NGS Flag id{value}

NGS_END


#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#endif
