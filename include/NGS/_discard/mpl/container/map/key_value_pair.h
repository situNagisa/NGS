#pragma once

#include "NGS/mpl/container/pair.h"
#include "NGS/mpl/functor/equal.h"

NGS_MPL_BEGIN

template<class _Pair>
concept CKeyValuePair = requires() {
	typename _Pair::key_type;
	typename _Pair::value_type;
};

NGS_MPL_FUNCTION(key_value_pair, class _Key, class _Value) {
	NGS_MPL_TYPE key_type = _Key;
	NGS_MPL_TYPE value_type = _Value;
};

template< class _Key, class _Value>
using kv_pair_ = key_value_pair<_Key, _Value>;

NGS_MPL_FUNCTION(equal, CKeyValuePair _Left, CKeyValuePair _Right) <_Left,_Right> {
	NGS_MPL_TYPE result_type = ccpt::bool_<equal_v<typename _Left::key_type, typename _Right::key_type>>;
};

NGS_MPL_END
