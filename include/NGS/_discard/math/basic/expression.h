#pragma once

#include "NGS/math/defined.h"

NGS_MATH_BEGIN

template<class _Type>
inline constexpr bool _is_expression = requires(_Type t, const _Type t_cst) {
	typename _Type::expression_type;
	typename _Type::type_category;
	{ _Type::complexity } -> std::convertible_to<size_t>;
	{ t() } -> std::convertible_to<typename _Type::expression_type&>;
	{ t_cst() } -> std::convertible_to<const typename _Type::expression_type&>;
};
/**
 * @brief Expression concept
 *
 * @property type expression_type
 * @property type type_category
 * @property static size_t complexity
 * @property expression_type& operator()();
 * @property const expression_type& operator()()const;
*/
template<class  _Type = void>
concept CExpression = _is_expression<std::remove_cvref_t<_Type>>;

template<ccpt::CRPT _Expression>
struct NGS_DLL_API Expression {
protected:
	using self_type = Expression;
public:
	constexpr static size_t complexity = 0;
	using expression_type = _Expression;
	using type_category = void;

	constexpr Expression() = default;

	const Expression& operator=(const Expression&) = delete;

	constexpr expression_type& operator()() { return static_cast<expression_type&>(*this); }
	constexpr const expression_type& operator()()const { return static_cast<const expression_type&>(*this); }
};

NGS_CCPT_VERIFY(CExpression, Expression<int>);

NGS_MATH_END
