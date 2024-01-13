#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<vectors::scalar _Value>
struct internal
{
	NGS_MPL_ENVIRON_BEGIN(internal);
public:
	using value_type = _Value;

	constexpr internal() = default;
	constexpr internal(const value_type& min, const value_type& max) : _min(min), _max(max) {}
	constexpr internal(vectors::vector_with_extent<2> auto&& min_max)
		: _min(vectors::ops::access(NGS_PP_PERFECT_FORWARD(min_max), 0))
		, _max(vectors::ops::access(NGS_PP_PERFECT_FORWARD(min_max), 1))
	{}
	constexpr internal(const ::std::array<value_type, 2>& min_max)
		: _min(min_max[0])
		, _max(min_max[1])
	{}
	constexpr internal(const self_type&) = default;
	constexpr self_type& operator=(const self_type&) = default;

	template<::std::convertible_to<value_type> _V>
	constexpr internal(const internal<_V>& other) : _min(other.min()), _max(other.max()) {}
	template<::std::convertible_to<value_type> _V>
	constexpr self_type& operator=(const internal<_V>& other) { _min = other.min(); _max = other.max(); return *this; }

	constexpr auto&& min()const { return _min; }
	constexpr auto&& max()const { return _max; }

	constexpr bool contain(const value_type& value)const { return value >= _min && value <= _max; }
	constexpr bool contain(const self_type& other)const { return _min <= other._min && _max >= other._max; }

	constexpr bool is_intersect(const self_type& other)const { return _min <= other._max && _max >= other._min; }
	constexpr self_type intersect(const self_type& other)const { return { ::std::max(_min, other._min), ::std::min(_max, other._max) }; }

	constexpr self_type unions(const self_type& other)const { return { ::std::min(_min, other._min), ::std::max(_max, other._max) }; }

	constexpr auto length()const { return _max - _min; }

	constexpr bool operator==(const self_type& other)const { return _min == other._min && _max == other._max; }

	constexpr bool empty()const { return (_min - _max) <= ::std::numeric_limits<value_type>::epsilon(); }

	constexpr void normalize()
	{
		if (_min > _max)
			::std::swap(_min, _max);
	}
public:
	value_type _min{};
	value_type _max{};
};

template<class _V>
constexpr ::std::string to_string(const internal<_V>& value)
{
	return ::std::string("[") + to_strings::to_string(value.min()) + ", " + to_strings::to_string(value.max()) + "]";
}

NGS_LIB_END