﻿#pragma once

#include "NGS/mpl/defined.h"
#include "NGS/mpl/meta_struct/meta_struct.h"
#include "NGS/mpl/container/vector.h"

NGS_MPL_BEGIN

NGS_mfunction(_convert_meta_struct_to_sequence, CMetaStruct _MetaStruct) {
	NGS_mcst_t result_type = typename _MetaStruct::variable_types;
};
template<CMetaStruct _MetaStruct>
using _convert_meta_struct_to_sequence_t = typename _convert_meta_struct_to_sequence<_MetaStruct>::result_type;

NGS_mfunction(_spread_meta_struct, CVector);
template<CVector _Vector>
using _spread_meta_struct_t = typename _spread_meta_struct<_Vector>::result_type;

// vector<var_> -> vector<var_>
NGS_mfunction(_spread_meta_struct, CVariable _Variable) < vector<_Variable> > {
	NGS_mcst_t result_type = vector<_Variable>;
};
// vector<struct_> -> vector<var_...>
NGS_mfunction(_spread_meta_struct, CMetaStruct _MetaStruct, ccpt::UInt _Count) < vector<variable<_MetaStruct, _Count>> > {
	NGS_mcst_t result_type = _spread_meta_struct_t<_convert_meta_struct_to_sequence_t<_MetaStruct>>;
};
// vector<var_, var_...> -> vector<var_, spread<var_...>>
NGS_mfunction(_spread_meta_struct, CVariable _Variable, CVariable... _Variables) < vector<_Variable, _Variables...> > {
	NGS_mcst_t result_type = push_front_t<_spread_meta_struct_t<vector<_Variables...>>, _Variable>;
};
// vector<struct_, var_...> -> vector<var_..., spread<struct_>>
NGS_mfunction(_spread_meta_struct, CMetaStruct _MetaStruct, size_t _Count, CVariable... _Variables) < vector<variable<_MetaStruct, ccpt::uint_<_Count>>, _Variables... > > {
	NGS_mcst_t result_type = push_front_range_t<_spread_meta_struct_t<vector<_Variables...>>, _spread_meta_struct_t<_convert_meta_struct_to_sequence_t<_MetaStruct>>>;
};

NGS_mfunction(spread_struct, CMetaStruct _MetaStruct, class = _spread_meta_struct_t<_convert_meta_struct_to_sequence_t<_MetaStruct>>);
NGS_mfunction(spread_struct, CMetaStruct _MetaStruct, CVariable... _Variables) < _MetaStruct, vector<_Variables...> > {
	NGS_mcst_t result_type = meta_struct_c<_Variables...>;
};

/**
 * @brief 将结构体的元变量展开直至所有元变量都为基础变量
 *
 * @tparam _MetaStruct 元结构体
 *
 * @return 展开后的元结构体
 */
template<CMetaStruct _MetaStruct>
using spread_struct_t = typename spread_struct<_MetaStruct>::result_type;

NGS_MPL_END
