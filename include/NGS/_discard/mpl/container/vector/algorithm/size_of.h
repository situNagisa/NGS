#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/utils/size_of.h"

NGS_MPL_BEGIN

template<template<class...>class _Sequence, class... _Element>
	requires CVector<_Sequence<_Element...>>
struct size_of<_Sequence<_Element...>> {
	NGS_MPL_TYPE result_type = ccpt::uint_<(size_of_v<_Element> +...)>;
};

NGS_MPL_END
