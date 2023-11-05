#pragma once

/**
 * \brief 获取表达式类型
 * \param expression
 * \return 表达式类型
 */
#define NGS_PP_EXPRESSION_TYPE(expression) decltype((expression))