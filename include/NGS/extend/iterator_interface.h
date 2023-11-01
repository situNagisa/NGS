#pragma once

#include "NGS/base/base.h"

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/reverse_iterator.hpp>

NGS_BEGIN
namespace iterator_interface {

template<class  _Derived, bool _Constant, class  _Rng, class  _ElementType>
struct NGS_DLL_API random_access_iterator : boost::stl_interfaces::iterator_interface <
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
	using _self_type = random_access_iterator;
	using _iterator_type = _Derived;
	using _element_type = _ElementType;

private:
	constexpr static auto _GET_CONST_ELEMENT_TYPE() {
		if constexpr (std::is_pointer_v<_element_type>) {
			return std::add_pointer_t<std::add_const_t<std::remove_pointer_t<_element_type>>>();
		}
		else if constexpr (std::is_reference_v<_element_type>) {
			return std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<_element_type>>>();
		}
		else {
			return std::add_const_t<_element_type>();
		}
	}
protected:
	using _const_element_type = decltype(_GET_CONST_ELEMENT_TYPE());
	using _range_type = _Rng;

	using _range_ptr = std::conditional_t<_Constant, const _range_type*, _range_type*>;

	using _pointer = std::conditional_t<_Constant, const _element_type*, _element_type*>;
	using _reference = std::conditional_t<_Constant, _element_type, _element_type&>;
	using _difference_type = typename _base_type::difference_type;
public:
	using _base_type::_base_type;
	constexpr random_access_iterator(_range_ptr rng, _difference_type n) : _range(rng), _n(n) {}
	constexpr random_access_iterator(_range_ptr rng) : random_access_iterator(rng, 0) {}

	constexpr _iterator_type& operator+=(_difference_type n) { _n += n; return static_cast<_iterator_type&>(*this); }
	constexpr _difference_type operator-(_iterator_type other)const { return _n - other._n; }

protected:
	_range_ptr _range = nullptr;
	_difference_type _n = 0;
};

}
NGS_END
