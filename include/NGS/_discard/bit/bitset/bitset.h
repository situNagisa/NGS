#pragma once

#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


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

namespace _detail
{
	template<::std::size_t BitCount>
	struct bits
	{
		NGS_PP_INJECT_BEGIN(bits);
	public:

	};
}

template<::std::size_t BitCount>
struct set
{
	NGS_PP_INJECT_BEGIN(set);
public:
	using value_type = ::std::array<::std::byte, algorithm::bit_to_byte_ceil(BitCount)>;



	value_type _value;
};

NGS_LIB_MODULE_END