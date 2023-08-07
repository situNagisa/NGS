﻿#pragma once

#include "NGS/mla/base/expression.h"
#include "NGS/mla/vector/tag.h"
#include "NGS/mla/iterator_interface.h"


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

NGS_MLA_END