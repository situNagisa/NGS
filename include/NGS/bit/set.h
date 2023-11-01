#pragma once

#include "./defined.h"
#include "./operation.h"

#if NGS_COMPILER_IS_MSVC
#pragma warning(push)
#pragma warning(disable: 4293)
#endif

NGS_BIT_BEGIN

template<size_t _BitCount>
struct bit_wrapper;


template<size_t _BitCount> requires (_BitCount <= as_bit<uint64>())
class NGS_DLL_API bit_set {
protected:
	using self_type = bit_set;
public:
	static constexpr uint64 bit_count = _BitCount;
	static constexpr uint64 byte_count = as_byte(bit_count);
	using byte_type = byte_<byte_count>;
	using wrapper_type = bit_wrapper<bit_count>;
	static constexpr byte_type mask = static_cast<byte_type>(bits::mask(bit_count));

public:
	constexpr          bit_set() = default;
	explicit constexpr bit_set(byte_type data) : _data(data) {}

	constexpr auto value()const { return _data & mask; }
	constexpr void set(byte_type data) { _data = data; }
	constexpr void set(size_t index, bool boolean) { _data = static_cast<byte_type>(bits::set(_data, scope(index), boolean)); }
	constexpr auto test(size_t index)const { return bits::get(_data, scope(index)); }
	constexpr void reset() { _data = 0; }
	constexpr void flip(size_t index) { set(index, !test(index)); }
	constexpr void flip() { _data = ~_data; }

	explicit constexpr operator byte_type()const { return value(); }


	constexpr bool operator==(const self_type& other)const { return value() == other.value(); }
	constexpr wrapper_type operator[](size_t index);

	constexpr bool operator[](size_t index)const { return test(index); }

	constexpr self_type& operator&=(const self_type& other) { _data &= other.value(); return *this; }
	constexpr self_type& operator|=(const self_type& other) { _data |= other.value(); return *this; }
	constexpr self_type& operator^=(const self_type& other) { _data ^= other.value(); return *this; }
	constexpr self_type& operator<<=(size_t off) { _data <<= off; return *this; }
	constexpr self_type& operator>>=(size_t off) { (_data &= mask) >>= off; return *this; }

	constexpr self_type operator&(const self_type& other)const { return { _data & other.value() }; }
	constexpr self_type operator|(const self_type& other)const { return { _data | other.value() }; }
	constexpr self_type operator^(const self_type& other)const { return { _data ^ other.value() }; }
	constexpr self_type operator~()const { return ~_data; }
	constexpr self_type operator<<(size_t off) { return { _data << off }; }
	constexpr self_type operator>>(size_t off) { return { _data >> off }; }

	constexpr bool all()const { return !(~_data & mask); }
	constexpr bool any()const { return _data & mask; }
	constexpr bool none()const { return !any(); }

	constexpr size_t count()const { return std::popcount(value()); }

	constexpr bool is_single_bit()const { return std::has_single_bit(value()); }
	constexpr byte_type ceil()const { return std::bit_ceil(value()); }
	constexpr byte_type floor()const { return std::bit_floor(value()); }
	constexpr size_t width()const { return std::bit_width(value()); }

	constexpr size_t leading_zero()const { return std::countl_zero(value()) - (as_bit(byte_count) - bit_count); }
	constexpr size_t leading_one()const { return std::countl_one(value()); }
	constexpr size_t trailing_zero()const { return std::countr_zero(_data); }
	constexpr size_t trailing_one()const { return std::countr_one(_data); }

private:
	byte_type _data{};
};

template<size_t _BitCount>
struct bit_wrapper
{
protected:
	using self_type = bit_wrapper;
public:
	using set_type = bit_set<_BitCount>;

	constexpr bit_wrapper(set_type& set, size_t index)
		: _set(set)
		, _index(index)
	{}
	constexpr ~bit_wrapper()noexcept = default;

	constexpr self_type& operator=(const bool boolean)noexcept {
		_set.set(_index, boolean);
		return *this;
	}
	constexpr self_type& operator=(const self_type& other)noexcept {
		_set.set(_index, other._set.test(other._index));
		return *this;
	}
	constexpr self_type& flip()noexcept {
		_set.flip(_index);
		return *this;
	}
	constexpr bool operator~()const noexcept { return !(static_cast<bool>(*this)); }
	constexpr operator bool()const noexcept { return _set.test(_index); }

	set_type& _set;
	size_t _index;
};

template <size_t _BitCount> requires (_BitCount <= as_bit<unsigned long long>())
constexpr typename bit_set<_BitCount>::wrapper_type bit_set<_BitCount>::operator[](size_t index)
{
	return { *this, index };
}

NGS_BIT_END



#if NGS_COMPILER_IS_MSVC
#pragma warning(pop)
#endif