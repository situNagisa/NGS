#pragma once

#include "NGS/base/defined.h"

NGS_BEGIN

#define NGS_mcst_t using
#define NGS_mcst constexpr static

#define NGS_mfunction(meta_function,...)	\
template<__VA_ARGS__>						\
struct meta_function						\
//
#define NGS_mif(meta_function,...)		\
template<bool _Condition, __VA_ARGS__>		\
struct meta_function						\
//
#define NGS_mif_case(meta_function,...)	\
template<__VA_ARGS__>						\
struct meta_function						\
//

#define NGS_mreturn_t using type =
#define NGS_mreturn static constexpr auto value = 

#define NGS_mget_t(pro,...) typename __VA_ARGS__::pro
#define NGS_mget(pro,...) __VA_ARGS__::pro

#define NGS_mget_return_t(...) NGS_mget_t(type,__VA_ARGS__)
#define NGS_mget_return(...) NGS_mget(value,__VA_ARGS__)

NGS_END
