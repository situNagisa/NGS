#pragma once

#include "NGS/math/mla/base/expression.h"
#include "NGS/math/mla/vector/tag.h"
#include "NGS/math/mla/iterator_interface.h"
#include "NGS/math/mla/vector/expression/concept.h"

NGS_MLA_BEGIN

template<ccpt::CRPT<CVectorExpression<void>> _Expression>
class VectorExpression : public Expression<_Expression> {
private:
	using base_type = typename VectorExpression::self_type;
protected:
	using self_type = VectorExpression<_Expression>;
public:
	using type_category = tag::vector;
	constexpr static size_t dimension = 0;

	constexpr auto operator[](size_t i)const { return (*this)()(i); }

	//=================
	// iterator
	//=================
protected:
	template<bool _Constant>
	struct _iterator : ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type> {
	private:
		using _base_type = ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, typename base_type::expression_type::element_type>;
		using _self_type = _iterator<_Constant>;

		NGS_minherit_t(_reference, _base_type);
	public:
		using _base_type::_base_type;

		constexpr _reference operator*()const { return (*_base_type::_expr)()(_base_type::_n); }
	};
public:
	using iterator = _iterator<false>;
	using const_iterator = _iterator<true>;
	using reverse_iterator = boost::stl_interfaces::reverse_iterator<iterator>;
	using const_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_iterator>;

	constexpr const_iterator begin()const { return const_iterator(&(*this)(), 0); }
	constexpr const_iterator cbegin()const { return begin(); }

	constexpr const_iterator end()const { return const_iterator(&(*this)(), base_type::expression_type::dimension); }
	constexpr const_iterator cend()const { return end(); }

	constexpr const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
	constexpr const_reverse_iterator crbegin()const { return rbegin(); }

	constexpr const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
	constexpr const_reverse_iterator crend()const { return rend(); }
};

NGS_MLA_END
