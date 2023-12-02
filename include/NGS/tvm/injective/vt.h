#pragma once

#include "../defined.h"

#define NGS_TVM_VT_REGISTER(mapper,value_type_)								\
namespace mapper{															\
using value_type = value_type_;												\
template<value_type> struct type_map;										\
template<value_type _Value> using type = typename type_map<_Value>::type;	\
}																			\
//

#define NGS_TVM_VT_INSERT(mapper,type_,value_)															\
template<> struct mapper::type_map<static_cast<mapper::value_type>(value_)> { using type = type_; };	\
//