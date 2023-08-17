#pragma once

#include "NGS/math/mla/vector/expression/expression.h"

NGS_MLA_BEGIN

/**
 * @brief vector container concept
 *
 * @concept derived_from CVectorExpression
 *
 * @property function size_t size()const;
 * @property function assign(CVectorExpression auto&&);
 * @property sizeof == (sizeof(element_type) * dimension)
*/
template<class  _Container = void>
concept CVectorContainer = requires(_Container expr, const _Container expr_cst, VectorExpression<typename _Container::expression_type> other, size_t index, typename _Container::element_type element) {
	{ expr.assign(expr) } -> std::convertible_to<_Container&>;
	{ expr.assign(index, element) } -> std::convertible_to<_Container&>;
	{ expr.assign(index, expr_cst) } -> std::convertible_to<_Container&>;
		requires  CVectorExpression<_Container>;
	//	requires sizeof(typename _Container::expression_type) == (sizeof(typename _Container::element_type) * _Container::dimension);
};

template<ccpt::CRPT<CVectorContainer<>> _Derived, ccpt::UInt _Dim, class  _ElementType, class  = std::make_index_sequence<_Dim::value>>
class NGS_API  VectorContainer;

template<ccpt::CRPT<CVectorContainer<>> _Derived, size_t _Dim, class  _ElementType, size_t... _Index>
class NGS_API  VectorContainer<
	_Derived,
	std::integral_constant<size_t, _Dim>,
	_ElementType,
	std::index_sequence<_Index...>
> : public VectorExpression<_Derived> {
private:
	using base_type = typename VectorContainer::self_type;
protected:
	using self_type = VectorContainer;
public:
	NGS_minherit_t(expression_type, base_type);

	using element_type = _ElementType;
	using type_category = tag::vector_container;
	constexpr static size_t dimension = _Dim;

public:
	constexpr VectorContainer() = default;
	//===================
	// access
	//===================
	//constexpr element_type& operator[](size_t i) { return (*this)()(i); }
	constexpr element_type operator[](size_t i)const { return (*this)()(i); }

	//===================
	// assign
	//===================
	constexpr expression_type& assign(size_t index, element_type element) { return (*this)(); }
	constexpr expression_type& assign(size_t index, const CVectorExpression auto& expression) { return (*this)().assign(index, expression()(index)); }
	/*constexpr expression_type& assign(mpl::sequence_params_t<_Index, element_type>... value) {
		(((*this)().assign((_Index, value))), ...);
		return (*this)();
	}*/
	constexpr expression_type& assign(const CVectorExpression auto& expression) {
		(((*this)().assign(_Index, expression()(_Index))), ...);
		return (*this)();
	}
	expression_type& assign(const expression_type& other) {
		std::memcpy(this, &other, sizeof(expression_type));
		return (*this)();
	}

	expression_type& operator=(const self_type& other) {
		return (*this)().assign(other);
	}
	template<CVectorExpression _Expression>
	expression_type& operator=(const _Expression& expression) {
		return (*this)().assign(expression);
	}
	//=================
	// iterator
	//=================
	using base_type::begin;
	using base_type::rbegin;
	using base_type::end;
	using base_type::rend;

	typename base_type::iterator begin() { return typename base_type::iterator(&(*this)(), 0); }
	typename base_type::iterator end() { return typename base_type::iterator(&(*this)(), base_type::expression_type::dimension); }
	typename base_type::reverse_iterator rbegin() { return typename base_type::reverse_iterator(end()); }
	typename base_type::reverse_iterator rend() { return typename base_type::reverse_iterator(begin()); }


	//==================
	// API
	//==================

	using base_type::operator();
	//constexpr element_type& operator()(size_t i);
	constexpr element_type operator()(size_t i)const;
};

NGS_MLA_END