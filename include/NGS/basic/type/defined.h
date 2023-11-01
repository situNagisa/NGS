#pragma once

#include "../defined.h"

#define NGS_BASIC_TYPE_BEGIN NGS_BEGIN inline namespace basic_types {
#define NGS_BASIC_TYPE_END } NGS_END

#define NGS_BASIC_TYPE_DEFINE(type,id) 		\
using id				= type;             \
using id##_cst			= const type;       \
using id##_ref			= type&;            \
using id##_ref_cst		= const type&;   	\
using id##_right		= type&&;			\
using id##_right_cst	= const type&&;		\
using id##_ptr			= type*;            \
using id##_ptr_cst		= const type*		\
//