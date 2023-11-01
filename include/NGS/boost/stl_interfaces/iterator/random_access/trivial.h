#pragma once

#include "./base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

inline constexpr auto random_access_range_square_bracket_access = [](std::ranges::random_access_range auto&& range, auto&& index) { return range[index]; };

template<class _Derived, class _Range, auto _Access>
struct base_trivial_random_access_iterator;

template<class _Derived, std::ranges::random_access_range _Range, auto _Access = random_access_range_square_bracket_access>
	requires requires(_Range range, int index) { {_Access(range, index)} -> std::convertible_to<std::ranges::range_value_t<_Range>>; }
struct base_trivial_random_access_iterator : base_random_access_iterator<_Derived, std::ranges::range_value_t<_Range>> {
	NGS_MPL_ENVIRON2(base_trivial_random_access_iterator, base_random_access_iterator<_Derived, std::ranges::range_value_t<_Range>>);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	NGS_MPL_INHERIT_TYPE(reference, base_type);
	NGS_MPL_INHERIT_TYPE(pointer, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);

	using range_type = _Range;
	constexpr static auto range_access = _Access;
public:
	using base_type::base_type;
	constexpr base_trivial_random_access_iterator(range_type* pointer, difference_type index) : _pointer(pointer), _index(index) {}

	constexpr iterator_type& operator+=(difference_type n) {
		_index += n;
		return base_type::_derived();
	}
	constexpr difference_type operator-(self_type other)const { return other._index - _index; }

	constexpr decltype(auto) operator*()const { return range_access(*_pointer, _index); }

protected:
	range_type* _pointer = nullptr;
	difference_type _index = 0;
};

template<std::ranges::random_access_range _Range, auto _Access = random_access_range_square_bracket_access>
	requires requires(_Range range, int index) { {_Access(range, index)} -> std::convertible_to<std::ranges::range_value_t<_Range>>; }
struct trivial_random_access_iterator : base_random_access_iterator<trivial_random_access_iterator<_Range, _Access>, std::ranges::range_value_t<_Range>> {
	NGS_MPL_ENVIRON2(trivial_random_access_iterator, base_random_access_iterator<trivial_random_access_iterator<_Range, _Access>, std::ranges::range_value_t<_Range>>);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	NGS_MPL_INHERIT_TYPE(reference, base_type);
	NGS_MPL_INHERIT_TYPE(pointer, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);

	using range_type = _Range;
	constexpr static auto range_access = _Access;
public:
	using base_type::base_type;
	constexpr trivial_random_access_iterator(range_type* pointer, difference_type index) : _pointer(pointer), _index(index) {}

	constexpr iterator_type& operator+=(difference_type n) {
		_index += n;
		return base_type::_derived();
	}
	constexpr difference_type operator-(self_type other)const { return other._index - _index; }

	constexpr decltype(auto) operator*()const { return range_access(*_pointer, _index); }

protected:
	range_type* _pointer = nullptr;
	difference_type _index = 0;
};

NGS_BOOST_STL_INTERFACES_END
