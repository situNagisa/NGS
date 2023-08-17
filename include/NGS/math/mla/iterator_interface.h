#pragma once

#include "NGS/math/mla/defined.h"

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/reverse_iterator.hpp>

NGS_MLA_BEGIN

template<class  _Derived, bool _Constant, class  _Expression, class  _ElementType>
struct NGS_API random_access_iterator : boost::stl_interfaces::iterator_interface <
	_Derived,
	std::random_access_iterator_tag,
	_ElementType
> {
protected:
	using _base_type = boost::stl_interfaces::iterator_interface<
		_Derived,
		std::random_access_iterator_tag,
		_ElementType
	>;
	using _self_type = random_access_iterator<_Derived, _Constant, _Expression, _ElementType>;
	using _iterator_type = _Derived;
	using _element_type = _ElementType;
	using _expression_type = _Expression;

	using _expression_ptr = std::conditional_t<_Constant, const _expression_type*, _expression_type*>;
	using _pointer = std::conditional_t<_Constant, const _element_type*, _element_type*>;
	using _reference = std::conditional_t<_Constant, _element_type, _element_type&>;
	using _difference_type = typename _base_type::difference_type;
public:
	using _base_type::_base_type;
	constexpr random_access_iterator(_expression_ptr expr, _difference_type n) : _expr(expr), _n(n) {}
	constexpr random_access_iterator(_expression_ptr expr) : random_access_iterator(expr, 0) {}

	constexpr _reference operator*()const;
	constexpr _iterator_type& operator+=(_difference_type n) { _n += n; return static_cast<_iterator_type&>(*this); }
	constexpr _difference_type operator-(_iterator_type other)const { return _n - other._n; }

protected:
	_expression_ptr _expr = nullptr;
	_difference_type _n = 0;
};

NGS_MLA_END
