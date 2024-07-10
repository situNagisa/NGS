#pragma once

#include "../defined.h"

#define NGS_TVM_TV_REGISTER_DEFAULT(mapper,value_type_, default_value)		\
namespace mapper{															\
using value_type = value_type_;												\
template<class> constexpr value_type value = default_value;					\
}																			\
//

#define NGS_TVM_TV_REGISTER(mapper,value_type_)	NGS_TVM_TV_REGISTER_DEFAULT(mapper,value_type_,{})

#define NGS_TVM_TV_INSERT(mapper,type_,value_)									\
namespace mapper{																\
template<> constexpr value_type value<type_> = static_cast<value_type>(value_);	\
}																				\
//