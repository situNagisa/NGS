#pragma once

#include "../defined.h"

#define NGS_TVM_VV_REGISTER(mapper,key_type_,value_type_)	\
namespace mapper{											\
using key_type = key_type_;									\
using value_type = value_type_;								\
template<key_type> constexpr value_type value = {};			\
}															\
//

#define NGS_TVM_VV_INSERT(mapper,key_,value_)									\
namespace mapper{																\
template<> constexpr value_type value<key_> = static_cast<value_type>(value_);	\
}																				\
//