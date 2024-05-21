#pragma once

#include "NGS/basic/basic.h"

//#define NGS_MPL_VERSION 20240521

#define NGS_MPL_NS mpl

#if 0
#define NGS_MPL_BEGIN NGS_BEGIN namespace mpl{
#define NGS_MPL_END } NGS_END

#define NGS_MPL_ENVIRON_BEGIN(target)				\
protected:											\
	using self_type = target						\
//

#define NGS_MPL_ENVIRON(target)						\
private:											\
	using base_type = typename target::self_type;	\
protected:											\
	using self_type = target						\
//

/**
 * \brief 有的编译器不支持`NGS_PP_INJECT`，所以提供了这个宏
 * \param target 子类
 * \param ... 父类
 */
#define NGS_MPL_ENVIRON2(target,...)				\
private:											\
	using base_type = __VA_ARGS__;					\
protected:											\
	using self_type = target						\
//

#define NGS_MPL_TYPE using
#define NGS_MPL_VALUE constexpr static

#define NGS_MPL_FUNCTION(meta_function,...)	\
template<__VA_ARGS__>						\
struct NGS_DLL_API meta_function				\
//

#define NGS_MPL_INHERIT_TYPE(id,...) using id = typename __VA_ARGS__::id
#define NGS_MPL_INHERIT_VALUE(id,...) constexpr static auto id = __VA_ARGS__::id

#define NGS_MPL_INHERIT2(id,...) using __VA_ARGS__::id
#define NGS_MPL_INHERIT(id) NGS_MPL_INHERIT2(id,base_type)

#endif