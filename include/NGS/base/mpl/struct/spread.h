#pragma once

#include "NGS/base/mpl/struct/struct.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(_StructVarToMemberVar, class);
NGS_mfunction(_StructVarToMemberVar, CTemplate<member_var> _Var, size_t _Index) < _StructVar<_Var, std::integral_constant<size_t, _Index>> > {
	NGS_mreturn_t _Var;
};

NGS_mfunction(_MetaStructToSequence, class);
NGS_mfunction(_MetaStructToSequence, class... _StructVars) < meta_struct<_StructVars...> > {
	NGS_mreturn_t sequence<typename _StructVarToMemberVar<_StructVars>::type ...>;
};

NGS_mfunction(_MetaStructSpread, class);
NGS_mfunction(_MetaStructSpread, CTemplate<member_var> _Var) < sequence<_Var> > {
	NGS_mreturn_t sequence<_Var>;
};
NGS_mfunction(_MetaStructSpread, CTemplate<meta_struct> _Struct, size_t _Count) < sequence<member_var<_Struct, std::integral_constant<size_t, _Count>>> > {
	NGS_mreturn_t typename _MetaStructToSequence<_Struct>::type;
};
NGS_mfunction(_MetaStructSpread, CTemplate<member_var> _Var, CTemplate<member_var>... _Vars)
< sequence<_Var, _Vars...> > {
	NGS_mreturn_t typename push_front<typename _MetaStructSpread<sequence<_Vars...>>::type, _Var>::type;
};
NGS_mfunction(_MetaStructSpread, CTemplate<meta_struct> _Struct, size_t _Count, CTemplate<member_var>... _Vars)
< sequence<member_var<_Struct, std::integral_constant<size_t, _Count>>, _Vars...> > {
	NGS_mreturn_t typename push_front<typename _MetaStructSpread<sequence<_Vars...>>::type, typename _MetaStructSpread<typename _MetaStructToSequence<_Struct>::type>::type>::type;
};


NGS_mfunction(spread_struct, CTemplate<meta_struct> _Struct, class = typename _MetaStructSpread<typename _MetaStructToSequence<_Struct>::type>::type);
NGS_mfunction(spread_struct, CTemplate<meta_struct> _Struct, CTemplate<member_var>... _Var) < _Struct, sequence<_Var...> > {
	NGS_mreturn_t meta_struct_c<_Var...>;
};
/**
 * @brief 将结构体的元变量展开直至所有元变量都为基础变量
 *
 * @tparam _Struct 元结构体
 *
 * @return 展开后的元结构体
 */
template<CTemplate<meta_struct> _Struct>
using spread_struct_t = typename spread_struct<_Struct>::type;

NGS_END
NGS_END
