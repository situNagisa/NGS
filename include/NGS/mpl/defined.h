#pragma once

#include "NGS/basic/basic.h"
#include "NGS/concepts/concepts.h"

#define NGS_MPL_BEGIN NGS_BEGIN namespace mpl{
#define NGS_MPL_END } NGS_END

#define NGS_menvironment(target)				   \
private:										   \
	using base_type = typename target::self_type;  \
protected:										   \
	using self_type = target					   \
//

#define NGS_mcst_t using
#define NGS_mcst constexpr static

#define NGS_mfunction(meta_function,...)	\
template<__VA_ARGS__>						\
struct NGS_API meta_function				\
//

#define NGS_mif(meta_function,...)			\
template<bool _Condition, __VA_ARGS__>		\
struct NGS_API meta_function				\
//
#define NGS_mif_case(meta_function,...)		\
template<__VA_ARGS__>						\
struct NGS_API meta_function				\
//

#define NGS_mget_t(pro,...) typename __VA_ARGS__::pro
#define NGS_mget(pro,...) __VA_ARGS__::pro

#define NGS_minherit_t(id,...) using id = typename __VA_ARGS__::id
#define NGS_minherit(id,...) constexpr static auto id = __VA_ARGS__::id