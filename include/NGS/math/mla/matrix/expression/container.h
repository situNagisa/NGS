#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN

/**
 * @brief
 *
 * @concept derived_drom CMatrixExpression
 *
 * @property type layout_category *
 * @property element_type operator()(size_t i)const
 * @property _Container& assign(const CMatrixExpression&) *
 *
*/
template<class  _Container = void>
concept CMatrixContainer = CMatrixExpression<_Container> && requires(_Container container, const _Container container_cst, typename _Container::element_type element, size_t index, size_t row_index, size_t col_index) {
	typename _Container::layout_category;

	{ container_cst(0) } -> std::convertible_to<typename _Container::element_type>;

	{ container.assign(container_cst) } -> std::convertible_to<_Container&>;
	{ container.assign(index, element) } -> std::convertible_to<_Container&>;
	{ container.assign(row_index, col_index, element) } -> std::convertible_to<_Container&>;
	{ container.assign(row_index, col_index, container_cst) } -> std::convertible_to<_Container&>;
	//	requires (sizeof(_Container) == (sizeof(typename matrix_traits<_Container>::element_type) * matrix_traits<_Container>::col_count * matrix_traits<_Container>::row_count));
};


template<
	ccpt::CRPT<CMatrixContainer<>> _Derived,
	ccpt::UInt _Row, ccpt::UInt _Col,
	class  _ElementType,
	class  _Layout,
	class  = std::make_index_sequence<_Col::value* _Row::value>,
	class  = std::make_index_sequence<_Row::value>,
	class  = std::make_index_sequence<_Col::value>>
	struct NGS_API MatrixContainer;

/**
 * @brief
 *
 * @warning 请尽量不要依赖此基类的赋值类构造函数，此基类并没有任何内存占用，
 *			内存申请在子类，也就意味着调用此基类的赋值类构造函数会初始化子类的内存，
 *			可能会导致未定义行为（由于作者水平限制并不能确定这是否是未定义行为），若图方便想使用的话，
 *			请不要在初始化子类的成员变量（此基类会完成初始化）。
 */
template<
	ccpt::CRPT<CMatrixContainer<>> _Derived,
	size_t _Row, size_t _Col,
	class  _ElementType,
	class  _Layout,
	size_t... _Index,
	size_t... _RowIndex,
	size_t... _ColIndex>
struct NGS_API MatrixContainer<
	_Derived,
	std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>,
	_ElementType,
	_Layout,
	std::index_sequence<_Index...>,
	std::index_sequence<_RowIndex...>,
	std::index_sequence<_ColIndex...>>
	: MatrixExpression<_Derived>{
public:
	using base_type = MatrixContainer::self_type;
protected:
	using self_type = MatrixContainer<
		_Derived,
		std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>,
		_ElementType,
		_Layout,
		std::index_sequence<_Index...>,
		std::index_sequence<_RowIndex...>,
		std::index_sequence<_ColIndex...>>;
public:

	using element_type = _ElementType;
	using layout_category = _Layout;
	using type_category = tag::matrix_container;
	constexpr static size_t row_count = _Row;
	constexpr static size_t col_count = _Col;
	constexpr static size_t element_count = row_count * col_count;

	using expression_type = typename base_type::expression_type;

	constexpr static size_t major_count = is_row_major<layout_category> ? row_count : col_count;
	constexpr static size_t minor_count = is_row_major<layout_category> ? col_count : row_count;
public:
	constexpr MatrixContainer() = default;
	//===============
	// access
	//===============
	constexpr auto major(size_t major_index) {
		if constexpr (is_row_major<expression_type>) {
			return base_type::row(major_index);
		}
		else {
			return base_type::column(major_index);
		}
	}
	constexpr auto minor(size_t minor_index)const {
		if constexpr (is_row_major<expression_type>) {
			return base_type::column(minor_index);
		}
		else {
			return base_type::row(minor_index);
		}
	}

	//===============
	// API
	//===============

	using base_type::operator();
	constexpr element_type operator()(size_t i)const;
	constexpr element_type operator()(size_t i, size_t j)const;

	//================
	// assign
	//================
	constexpr expression_type& assign(size_t index, element_type element) { return (*this)(); }
	constexpr expression_type& assign(size_t row_index, size_t col_index, element_type element) { return (*this)(); }
	constexpr expression_type& assign(size_t row_index, size_t col_index, const CMatrixExpression auto& expression) { return (*this)().assign(row_index, col_index, expression()(row_index, col_index)); }

	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	constexpr expression_type& assign(const _Expression& expression) {
		if constexpr (is_row_major<layout_category>) {
			for (size_t row_index = 0; row_index < row_count; row_index++)
			{
				for (size_t col_index = 0; col_index < col_count; col_index++)
				{
					(*this)().assign(row_index, col_index, expression);
				}
			}
		}
		else if constexpr (is_col_major<layout_category>) {
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				for (size_t row_index = 0; row_index < row_count; row_index++)
				{
					(*this)().assign(row_index, col_index, expression);
				}
			}
		}
		return (*this)();
	}
	expression_type& assign(const expression_type& expression) {
		std::memcpy(this, &expression, sizeof(expression));
		return (*this)();
	}
	//template<CMatrixExpression _Expression> requires (is_similar<expression_type, _Expression>)
	//expression_type& operator=(const _Expression& target) { return (*this)().assign(target); }
	//template<CMatrixExpression _Expression> requires (is_similar<expression_type, _Expression>)
	//expression_type& operator=(_Expression&& target) { return (*this)().assign(target); }

	//expression_type& operator=(const expression_type& target) { return (*this)().assign(target); }
	template<class  T>
	expression_type& operator=(T&& target) { return (*this)().assign(std::forward<T>(target)); }
	expression_type& operator=(const self_type& target) { return (*this)().assign(target); }

	//=================
	// iterator
	//=================
protected:
	template<bool _Constant>
	struct NGS_API _iterator : ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, element_type> {
	private:
		using _base_type = ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, element_type>;
		NGS_minherit_t(_element_type, _base_type);
	public:
		using _base_type::_base_type;
		_element_type operator*()const { return (*_base_type::_expr)()(_base_type::_n); }
	};
public:
	using iterator = _iterator<false>;
	using const_iterator = _iterator<true>;
	using reverse_iterator = boost::stl_interfaces::reverse_iterator<iterator>;
	using const_reverse_iterator = boost::stl_interfaces::reverse_iterator<const_iterator>;

	const_iterator begin()const { return const_iterator(&(*this)(), 0); }
	const_iterator cbegin()const { return begin(); }

	const_iterator end()const { return const_iterator(&(*this)(), element_count); }
	const_iterator cend()const { return end(); }

	const_reverse_iterator rbegin()const { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin()const { return rbegin(); }

	const_reverse_iterator rend()const { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend()const { return rend(); }

	iterator begin() { return iterator(&(*this)(), 0); }
	iterator end() { return iterator(&(*this)(), element_count); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
};


NGS_MLA_END
