#pragma once

#include "./tv.h"
#include "./vt.h"

#define NGS_TVM_REGISTER(mapper,value_type_)	\
NGS_TVM_TV_REGISTER(mapper,value_type_);		\
NGS_TVM_VT_REGISTER(mapper,value_type_)			\
//

#define NGS_TVM_INSERT(mapper,type_,value_)	\
NGS_TVM_TV_INSERT(mapper,type_,value_);		\
NGS_TVM_VT_INSERT(mapper,type_,value_)		\
//