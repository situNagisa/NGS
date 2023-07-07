//==========================================================================================================
// @file	:	NGS/NGS
// @CLR		:	4.0.30319.42000
// @author	:	NAGISA
// @data	:	2023/4/7 16:04:40
// @brief	:	
//==========================================================================================================
#pragma once

/**
 * 命名规范：
 * 类名/结构/枚举/联合：	大驼峰
 * 私有类名/结构/枚举/联合：_大驼峰
 *
 * 公有成员函数：			大驼峰
 * 公有成员变量：			小写蛇形
 * 私有成员函数：			_大驼峰
 * 私有成员变量：			_小写蛇形
 *
 * 静态成员函数：			全大写蛇形
 * 静态成员变量：
 *
 * 全局函数：				大驼峰
 * 全局变量：
 * 全局静态函数：			_全大写蛇形
 * 全局静态变量：
 *
 * 元函数：				小写蛇形
 * 元函数类：				小写蛇形
 *
 * 宏名：				NGS_全大写蛇形
 * 接口：				I大驼峰
 * 概念：				C大驼峰
 * 模板参数：				_大驼峰
 *
 */

 //NGS_USE_HPP
 //NGS_USE_EMBEDDED
 //NGS_USE_NSL
 //NGS_USE_NSW

#define NGS_USE_HPP 1

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"
#include "NGS/algorithm/algorithm.h"

#ifdef NGS_USE_EMBEDDED
#include "NGS/embedded/embedded.h"
#endif

#ifdef NGS_USE_NSL
#include "NGS/nsl/NSL.h"
#endif

#ifdef NGS_USE_NSW
#include "NGS/nsw/NSW.h"
#endif

#if _MSC_VER

//#pragma comment(lib,"NGS.lib")

#endif // USE_NGS_MODULE
