#pragma once

#include "./concept.h"

NGS_META_STRUCT_TYPE_BEGIN

template<class...>
struct structure;

template<CStructureDescribe _Describe>
struct structure<_Describe> : _Describe, struct_storage<_Describe> {};

template<layout::CAlign _Align, CVariable... _Variable>
struct structure<_Align, _Variable...> : structure<struct_describe<_Align, _Variable...>> {};

template<CVariable... _Variable>
struct structure<_Variable...> : structure<layout::default_align_t,_Variable...> {};

template<layout::CAlign _Align, class... _Types>
struct structure<_Align, _Types...> : structure<_Align, variable<_Types>...> {};

template<class... _Types>
struct structure<_Types...> : structure<variable<_Types>...> {};


NGS_META_STRUCT_TYPE_END
