#pragma once

#include "NGS/math/mla/defined.h"
#include "NGS/math/mla/base/concepts.h"
#include "NGS/math/mla/base/tag.h"

NGS_MLA_BEGIN


/**
 * @brief Expression concept
 *
 * @property type expression_type
 * @property type type_category
 * @property static size_t complexity
 * @property expression_type& operator()();
 * @property const expression_type& operator()()const;
*/
template<class  T>
concept CExpression = requires(T t, const T t_cst) {
	typename T::expression_type;
	typename T::type_category;
	{ T::complexity } -> std::convertible_to<size_t>;
	{ t() } -> std::convertible_to<typename T::expression_type&>;
	{ t_cst() } -> std::convertible_to<const typename T::expression_type&>;
};

template<ccpt::CRPT _Expression>
struct NGS_API Expression {
protected:
	using self_type = Expression<_Expression>;
public:
	constexpr static size_t complexity = 0;
	using expression_type = _Expression;
	using type_category = tag::unknown;

	constexpr Expression() = default;

	const Expression& operator=(const Expression&) = delete;

	constexpr expression_type& operator()() { return static_cast<expression_type&>(*this); }
	constexpr const expression_type& operator()()const { return static_cast<const expression_type&>(*this); }
};

NGS_CCPT_VERIFY(CExpression, Expression<int>);

NGS_MLA_END
