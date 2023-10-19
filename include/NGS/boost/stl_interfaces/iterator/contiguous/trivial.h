#pragma once

#include "./base.h"

NGS_BOOST_STL_INTERFACES_BEGIN

template<class _Derived_or_ElementType, class _ElementType = void>
struct trivial_contiguous_iterator;

template<class _Derived, class _ElementType>
struct trivial_contiguous_iterator : base_contiguous_iterator<_Derived,_ElementType> {
	NGS_MPL_ENVIRON2(trivial_contiguous_iterator, base_contiguous_iterator<_Derived, _ElementType>);
public:
	NGS_MPL_INHERIT_TYPE(iterator_type, base_type);
	NGS_MPL_INHERIT_TYPE(value_type, base_type);
	NGS_MPL_INHERIT_TYPE(reference, base_type);
	NGS_MPL_INHERIT_TYPE(pointer, base_type);
	NGS_MPL_INHERIT_TYPE(difference_type, base_type);
public:
	using base_type::base_type;
	constexpr trivial_contiguous_iterator(pointer pointer) : _pointer(pointer) {}
	constexpr trivial_contiguous_iterator() = default;

	constexpr iterator_type& operator+=(difference_type n) {
		_pointer += n;
		return base_type::_derived();
	}
	constexpr difference_type operator-(self_type other)const { return other._ponter - _pointer; }

	constexpr reference operator*()const { return *_pointer; }

protected:
	pointer _pointer = nullptr;
};

template<class _ElementType>
struct trivial_contiguous_iterator<_ElementType, void> :
	trivial_contiguous_iterator< trivial_contiguous_iterator<_ElementType>, _ElementType> {
	NGS_MPL_ENVIRON(trivial_contiguous_iterator);
public:
};

NGS_BOOST_STL_INTERFACES_END
