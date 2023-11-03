#pragma once

#include "./base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<class _Derived, class _Range, class _ElementType, auto _Access>
	requires requires(_Range range, int index) { {_Access(range, index)} -> std::convertible_to<_ElementType>; }
struct base_trivial_random_access_iterator : base_random_access_iterator<_Derived, _ElementType> {
	NGS_MPL_ENVIRON2(base_trivial_random_access_iterator, base_random_access_iterator<_Derived, _ElementType>);
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
	constexpr base_trivial_random_access_iterator(const self_type&) = default;

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

template<class _Range, class _ElementType, auto _Access>
	requires requires(_Range range, int index) { {_Access(range, index)} -> std::convertible_to<_ElementType>; }
struct trivial_random_access_iterator : base_random_access_iterator<trivial_random_access_iterator<_Range, _ElementType, _Access>, _ElementType> {
	NGS_MPL_ENVIRON2(trivial_random_access_iterator, base_random_access_iterator<trivial_random_access_iterator<_Range, _ElementType, _Access>, _ElementType>);
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
	constexpr trivial_random_access_iterator(const self_type&) = default;

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
