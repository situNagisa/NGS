#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

NGS_mfunction(find_if, class _Rng, template<class...>class _Predicate, class...);

template<class _Rng, template<class...>class _Predicate,class... _Args>
using find_if_t = typename find_if<_Rng, _Predicate,_Args...>::result_type;

NGS_MPL_END
