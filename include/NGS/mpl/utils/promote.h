#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(promote, class _Left,class _Right, class... _Types) {
private:
	static constexpr auto _get_result_type() {
		if constexpr (sizeof...(_Types)) {
			return declval<typename promote<typename promote<_Left, _Right>::result_type, _Types...>::result_type>();
		}
		else {
			return (declval<_Left>() + declval<_Right>());
		}
	}
public:
	NGS_mcst_t result_type = decltype(_get_result_type());
};

template<class _Left, class _Right,class... _Types>
using promote_t = typename promote<_Left, _Right,_Types...>::result_type;

NGS_MPL_END
