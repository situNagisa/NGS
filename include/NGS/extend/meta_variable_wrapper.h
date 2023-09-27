#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/concepts.h"

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/reverse_iterator.hpp>

NGS_BEGIN

template<mpl::CMetaVariable _Var, ccpt::Bool _Const>
struct meta_variable_wrapper {
protected:
	using self_type = meta_variable_wrapper;
public:
	using variable_type = _Var;
	using element_type = std::conditional_t<_Const::value,
		std::add_const_t<typename variable_type::element_type>,
		typename variable_type::element_type>;
public:
	constexpr explicit(false) meta_variable_wrapper(element_type* pointer) : pointer(pointer) {}

	constexpr explicit(true) operator element_type* ()const { return pointer; }

	constexpr auto& operator*()const { return *pointer; }
	constexpr auto operator->()const { return pointer; }
	constexpr auto& operator[](size_t index)const { return pointer[index]; }

	constexpr size_t size()const { return variable_type::element_count; }
	constexpr auto data()const { return pointer; }

	struct NGS_API const_iterator : boost::stl_interfaces::iterator_interface<const_iterator, std::random_access_iterator_tag, element_type> {
	protected:
		using _base_type = boost::stl_interfaces::iterator_interface<const_iterator, std::random_access_iterator_tag, element_type>;
		using _self_type = const_iterator;
		using _iterator_type = _self_type;

		using _difference_type = typename _base_type::difference_type;
	public:
		using _base_type::_base_type;
		explicit(false) constexpr const_iterator(element_type* pointer) : _pointer(pointer) {}

		constexpr element_type& operator*()const { return *_pointer; }
		constexpr _iterator_type& operator+=(_difference_type n) { _pointer += n; return static_cast<_iterator_type&>(*this); }
		constexpr _difference_type operator-(_iterator_type other)const { return _pointer - other._pointer; }

	protected:
		element_type* _pointer = nullptr;
	};
	using iterator_type = const_iterator;
	using const_iterator_type = const_iterator;
	using reverse_iterator_type = boost::stl_interfaces::reverse_iterator<iterator_type>;
	using const_reverse_iterator_type = boost::stl_interfaces::reverse_iterator<const_iterator_type>;

	constexpr iterator_type begin() { return iterator_type(pointer); }
	constexpr iterator_type end() { return iterator_type(pointer + size()); }
	constexpr const_iterator_type begin()const { return const_iterator_type(pointer); }
	constexpr const_iterator_type end()const { return const_iterator_type(pointer + size()); }
	constexpr const_iterator_type cbegin()const { return begin(); }
	constexpr const_iterator_type cend()const { return end(); }

	constexpr reverse_iterator_type rbegin() { return reverse_iterator_type(end()); }
	constexpr reverse_iterator_type rend() { return reverse_iterator_type(begin()); }
	constexpr const_reverse_iterator_type rbegin()const { return const_reverse_iterator_type(end()); }
	constexpr const_reverse_iterator_type rend()const { return const_reverse_iterator_type(begin()); }
	constexpr const_reverse_iterator_type crbegin()const { return rbegin(); }
	constexpr const_reverse_iterator_type crend()const { return crend(); }

	template<class _Type>
	constexpr self_type& operator=(const _Type& param)
		requires (std::ranges::input_range<_Type>) &&
	(std::convertible_to<std::ranges::range_value_t<_Type>, element_type>)
	{
		std::ranges::copy(param, begin());
		return *this;
	}
	template<class _Type>
	constexpr self_type& operator=(const _Type& param)
		requires (variable_type::element_count == 1) &&
	(std::convertible_to<_Type, element_type>) &&
		(std::assignable_from<element_type&, _Type>)
	{
		*pointer = param;
		return *this;
	}
	template<class _Type>
	constexpr self_type& operator=(const _Type& param)
		requires (variable_type::element_count == 1) &&
	(std::ranges::input_range<_Type>) &&
		(!std::convertible_to<_Type, element_type>) &&
		(std::ranges::output_range<element_type, std::ranges::range_value_t<_Type>>) &&
		(std::convertible_to<std::ranges::range_value_t<_Type>, std::ranges::range_value_t<element_type>>)
	{
		std::ranges::copy(param, std::ranges::begin(pointer[0]));
		return *this;
	}
public:
	element_type* pointer = nullptr;
};

template<mpl::CMetaVariable _V, ccpt::Bool _C>
constexpr std::string to_string(const meta_variable_wrapper<_V, _C>& wrapper) {
	if constexpr (_V::element_count > 1) {
		std::string result{};
		result += '{';
		for (auto i = wrapper.begin(); i != wrapper.end(); ++i)
		{
			if (i != wrapper.begin()) {
				result += ", ";
			}
			result += to_string(*i);
		}
		result += '}';
		return result;
	}
	else {
		return to_string(*wrapper);
	}
}

NGS_END