#pragma once

#include "NGS/mla/base/expression.h"
#include "NGS/mla/vector/tag.h"

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/reverse_iterator.hpp>


NGS_MLA_BEGIN

/**
 * @brief Vector expression concept
 *
 * @concept CExpression
 *
 * @property static size_t dimension
 * @property type element_type
 * @property function element_type operator()(size_t);
 * @property function element_type operator()(size_t)const;
*/
template<class T = void>
concept CVectorExpression = CExpression<T> && requires(T expr, const T expr_cst) {
	typename T::element_type;
	{ T::dimension } -> std::convertible_to<size_t>;
	{ expr(0) } -> std::convertible_to<typename T::element_type>;
	{ expr_cst(0) } -> std::convertible_to<typename T::element_type>;
		requires std::derived_from<typename T::type_category, tag::vector>;
};

template<ccpt::CRPT<CVectorExpression<void>> _Expression>
class VectorExpression : public Expression<_Expression> {
private:
	using base_type = typename VectorExpression::self_type;
protected:
	using self_type = VectorExpression<_Expression>;
public:
	using type_category = tag::vector;
	constexpr static size_t dimension = 0;

	//=================
	// iterator
	//=================
protected:
	template<bool _Constant>
	struct _iterator : boost::stl_interfaces::iterator_interface <
		_iterator<_Constant>,
		std::random_access_iterator_tag,
		typename base_type::expression_type::element_type
	> {
	private:
		using _base_type = boost::stl_interfaces::iterator_interface<
			_iterator<_Constant>,
			std::random_access_iterator_tag,
			typename base_type::expression_type::element_type
		>;
		using _element_type = typename base_type::expression_type::element_type;
		using _expression_ptr = std::conditional_t<_Constant,const typename base_type::expression_type*,typename base_type::expression_type*>;
		using _pointer = std::conditional_t<_Constant, const _element_type*, _element_type*>;
		using _refence = std::conditional_t<_Constant, _element_type, _element_type&>;
		using _self = _iterator<_Constant>;
		using _difference_type = typename _base_type::difference_type;
	public:
		using _base_type::_base_type;
		constexpr _iterator(_expression_ptr expr,_difference_type n) : _expr(expr),_n(n) {}
		constexpr _iterator(_expression_ptr expr) : _iterator(expr,0) {}

		_refence operator*()const { return (*_expr)()(_n); }
		_self& operator+=(_difference_type n) { _n += n; return *this; }
		_difference_type operator-(_self other)const { return _n - other._n; }

	private:
		_expression_ptr _expr = nullptr;
		_difference_type _n = 0;
	};
public:
	using iterator = _iterator<false>;
	using const_iterator = _iterator<true>;
	using reverse_iterator = boost::stl_interfaces::reverse_iterator<iterator>;
	using const_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_iterator>;

	const_iterator begin()const { return const_iterator(&(*this)(), 0); }
	const_iterator cbegin()const { return begin(); }

	const_iterator end()const { return const_iterator(&(*this)(), base_type::expression_type::dimension); }
	const_iterator cend()const { return end(); }

	const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin()const { return rbegin(); }

	const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend()const { return rend(); }
};

NGS_MLA_END
