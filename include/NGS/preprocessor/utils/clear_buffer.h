#pragma once

/**
 * \brief 编译器在调用常量表达式时，若模板参数与之前某一次调用相同，则会返回之前的结果，
 * 此宏作为模板参数用于清除缓存，强制编译器重新计算常量表达式
 */
#define NGS_PP_CONSTEXPR_CLEAR_BUFFER auto = []{}