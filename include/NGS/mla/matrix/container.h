#pragma once

#include "NGS/mla/matrix/expression/matrix.h"
#include "NGS/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<class _Container = void>
concept CMatrixContainer = CMatrixExpression<_Container> && requires(_Container container, const _Container container_cst) {
	typename _Container::layout_category;


	{ container(0) } -> std::convertible_to<typename _Container::element_type>;
	{ container_cst(0) } -> std::convertible_to<typename _Container::element_type>;

	{ container.assign(container_cst) } -> std::convertible_to<_Container&>;
		requires (sizeof(_Container) == (sizeof(typename matrix_traits<_Container>::element_type) * matrix_traits<_Container>::col_count * matrix_traits<_Container>::row_count));
};


template<
	ccpt::CRPT<CMatrixContainer<>> _Derived,
	ccpt::UInt _Row, ccpt::UInt _Col,
	class _ElementType,
	class _Layout,
	class = std::make_index_sequence<_Col::value* _Row::value>,
	class = std::make_index_sequence<_Row::value>,
	class = std::make_index_sequence<_Col::value>>
	struct MatrixContainer;

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
	class _ElementType,
	class _Layout,
	size_t... _Index,
	size_t... _RowIndex,
	size_t... _ColIndex>
struct MatrixContainer<
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
	constexpr static size_t row_count = _Row;
	constexpr static size_t col_count = _Col;
	constexpr static size_t element_count = row_count * col_count;

	using expression_type = typename base_type::expression_type;

	constexpr static size_t major_count = is_row_major<layout_category> ? row_count : col_count;
	constexpr static size_t minor_count = is_row_major<layout_category> ? col_count : row_count;
protected:
	template<size_t _Index> using _element_i_t = element_type;
	template<size_t _RowI, size_t _ColI> using _element_r_c_t = element_type;
public:
	constexpr MatrixContainer() = default;
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	constexpr MatrixContainer(const _Expression& expression) {
		for (size_t row_index = 0; row_index < row_count; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				(*this)()(row_index, col_index) = expression()(row_index, col_index);
			}
		}
	}
	constexpr MatrixContainer(_element_i_t<_Index>... value) {
		for (size_t row_index = 0; row_index < row_count; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				(*this)()(row_index, col_index) = value;
			}
		}
	}
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
	constexpr element_type& operator()(size_t i);
	constexpr const element_type& operator()(size_t i)const;

	constexpr element_type& operator()(size_t row_index, size_t col_index);
	constexpr const element_type& operator()(size_t i, size_t j)const;

	//================
	// assign
	//================
	expression_type& assign(_element_i_t<_Index>... value) {
		(((*this)()(_Index) = value), ...);
		return (*this)();
	}
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	expression_type& assign(const _Expression& expression) {
		for (size_t row_index = 0; row_index < row_count; row_index++)
		{
			for (size_t col_index = 0; col_index < col_count; col_index++)
			{
				(*this)()(row_index, col_index) = expression()(row_index, col_index);
			}
		}
		return (*this)();
	}
	expression_type& assign(const expression_type& expression) {
		std::memcpy(this, &expression, sizeof(element_type) * element_count);
	}
	template<CMatrixExpression _Expression>
		requires (is_similar<expression_type, _Expression>)
	expression_type& operator=(const _Expression& expression) { return assign(expression); }
	expression_type& operator=(const expression_type& expression) { return assign(expression); }

	//=================
	// iterator
	//=================
protected:
	template<bool _Constant>
	struct _iterator : ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, element_type> {
	private:
		using _base_type = ngs::mla::random_access_iterator<_iterator<_Constant>, _Constant, typename base_type::expression_type, element_type>;
		NGS_minherit_t(_reference, _base_type);
	public:
		using _base_type::_base_type;
		_reference operator*()const { return (*_base_type::_expr)()(_base_type::_n); }
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
