#pragma once

#include "./defined.h"

NGS_YAP_BEGIN

/**
 * @brief Expression concept
 *
 * @property type expression_type
 * @property type expression_category
 * @property static size_t complexity
 * @property expression_type& operator()();
 * @property const expression_type& operator()()const;
*/
template<class _Type = void,class _ObjectType = std::remove_reference_t<_Type>>
concept CExpression = requires(_ObjectType t, const _ObjectType t_cst) {
	typename _ObjectType::expression_type;
	typename _ObjectType::expression_category;

	{ _ObjectType::complexity } -> std::convertible_to<size_t>;
};

NGS_YAP_END
