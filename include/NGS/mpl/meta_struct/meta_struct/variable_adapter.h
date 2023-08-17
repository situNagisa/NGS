#pragma once

#include "NGS/mpl/defined.h"
#include "NGS/mpl/meta_struct/variable.h"
#include "NGS/mpl/container/vector.h"

NGS_MPL_BEGIN

template<class _Adapter>
concept _CVariableAdapter = requires() {
	{ _Adapter::index } -> std::convertible_to<size_t>;
		requires CVariable<typename _Adapter::variable_type>;
};

NGS_mfunction(_variable_adapter, CVariable _Var, ccpt::UInt _Index) {
	NGS_mcst size_t index = _Index::value;
	NGS_mcst_t variable_type = _Var;
};

template<CVariable _Var, size_t _Index>
using _variable_adapter_c = _variable_adapter<_Var, ccpt::uint_<_Index>>;

NGS_CCPT_VERIFY(_CVariableAdapter, _variable_adapter_c<var_<int, 2>, 0>);

NGS_MPL_END
