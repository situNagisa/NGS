﻿#pragma once

#define _NGS_CONVERT_EXPRESSION_TO_STRING(expression)	#expression
/**
 * \brief 将表达式转换为字符串
 * \param expression 表达式
 */
#define NGS_TO_STRING(expression)						_NGS_CONVERT_EXPRESSION_TO_STRING(expression)
