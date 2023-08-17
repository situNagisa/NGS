﻿#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

template<class _Sequence>
concept CVector = requires(_Sequence sequence, const _Sequence sequence_cst) {
	typename _Sequence::template at<ccpt::uint_<0>>;
	typename _Sequence::template at_c<0>;
	{ _Sequence::size } -> std::convertible_to<size_t>;
};

NGS_mfunction(vector, class... _Element) : protected std::tuple<_Element...>{
private:
	using base_type = std::tuple<_Element...>;
protected:
	using self_type = vector;
public:
	NGS_mcst size_t size = std::tuple_size_v<base_type>;
	template<ccpt::UInt _Index>
	NGS_mcst_t at = std::tuple_element_t<_Index::value, base_type>;
	template<size_t _Index>
	NGS_mcst_t at_c = at<ccpt::uint_<_Index>>;
};

NGS_MPL_END
