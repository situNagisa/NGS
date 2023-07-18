#pragma once

#include "NGS/base/mpl/struct/struct.h"
#include "NGS/base/mpl/struct/spread.h"

NGS_BEGIN
NGS_MPL_BEGIN

NGS_mfunction(meta_struct_vars, CMetaStruct);
NGS_mfunction(meta_struct_vars, class... _SVars) < meta_struct<_SVars...> > {
	NGS_mreturn_t boost::mpl::vector<typename _SVars::type...>;
};

template<CMetaStruct... _Struct>
using meta_struct_vars_t = typename meta_struct_vars<spread_struct_t<meta_struct_c<var_<_Struct>...>>>::type;

NGS_END
NGS_END
