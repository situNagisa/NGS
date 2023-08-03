#pragma once

#include "NGS/mla/vector/expression.h"

NGS_MLA_BEGIN

template<ccpt::CRPT<CVectorExpression<>> _Derived, ccpt::UInt _Dim, class _ElementType, class = std::make_index_sequence<_Dim::value>>
class BasicVector;

/**
 * @brief 
 * 
 * @warning 请尽量不要依赖此基类的赋值类构造函数，此基类并没有任何内存占用，
 *			内存申请在子类，也就意味着调用此基类的赋值类构造函数会初始化子类的内存，
 *			可能会导致未定义行为（由于作者水平限制并不能确定这是否是未定义行为），若图方便想使用的话，
 *			请不要在初始化子类的成员变量（此基类会完成初始化）。
 */
template<ccpt::CRPT<CVectorExpression<>> _Derived, size_t _Dim, class _ElementType, size_t... _Index>
class BasicVector<
	_Derived,
	std::integral_constant<size_t, _Dim>,
	_ElementType,
	std::index_sequence<_Index...>
> : public VectorExpression<_Derived> {
private:
	using base_type = typename BasicVector::self_type;
protected:
	using self_type = BasicVector<_Derived, std::integral_constant<size_t, _Dim>, _ElementType, std::index_sequence<_Index...>>;
public:
	using element_type = _ElementType;
	constexpr static size_t dimension = _Dim;

private:
	template<size_t _I>using _element_i_t = element_type;
public:
	constexpr BasicVector() = default;
	/**
	 * @brief construct from expression
	 * 
	 * @param expression
	 */
	constexpr BasicVector(CVectorExpression auto&& expression) {
		(((*this)()(_Index) = expression()(_Index)), ...);
	}
	constexpr BasicVector(_element_i_t<_Index>... value) {
		(((*this)()(_Index) = value),...);
	}

	constexpr size_t size()const { return _Dim; }

	using base_type::operator();
	constexpr element_type& operator()(size_t i);
	constexpr const element_type& operator()(size_t i)const;
};

template<size_t _Dim, class _ElementType>
class Vector : public BasicVector<Vector<_Dim, _ElementType>, std::integral_constant<size_t, _Dim>, _ElementType> {
public:
	using base_type = typename Vector::self_type;
protected:
	using self_type = Vector<_Dim, _ElementType>;
public:
	using element_type = typename base_type::element_type;

	using base_type::base_type;

	using base_type::operator();
	constexpr element_type& operator()(size_t i) { return _data[i]; }
	constexpr const element_type& operator()(size_t i)const { return _data[i]; }

private:
	element_type _data[_Dim];
};
NGS_CCPT_VERIFY(CVectorExpression, Vector<3, int>);

NGS_MLA_END
