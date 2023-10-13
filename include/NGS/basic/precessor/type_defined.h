#pragma once

#define NGS_TYPE_DEFINE(type,id)        \
using __##id    = type;                 \
using __##id##_cst = const type;        \
using __##id##_ref = type&;             \
using __##id##_ref_cst = const type&;   \
using __##id##_right = type&&;			\
using __##id##_right_cst = const type&&;\
using __##id##_ptr = type*;             \
using __##id##_ptr_cst = const type*;	\
//


#define _NGS_TYPE_DEFINE(type,id)   	\
using id    = type;                 	\
using id##_cst = const type;        	\
using id##_ref = type&;             	\
using id##_ref_cst = const type&;   	\
using id##_right = type&&;				\
using id##_right_cst = const type&&;	\
using id##_ptr = type*;             	\
using id##_ptr_cst = const type*;		\
//

#define NGS_DEFINE_TYPE(id,...)			\
using id##_t = __VA_ARGS__;				\
using id##_cst = const id##_t;			\
using id##_ref = id##_t&;				\
using id##_ref_cst = const id##_t&;		\
using id##_rref = id##_t&&;				\
using id##_rref_cst = const id##_t&&;	\
using id##_ptr = id##_t*;				\
using id##_ptr_cst = const id##_t*		\
//