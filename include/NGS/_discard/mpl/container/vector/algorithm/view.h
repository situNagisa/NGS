#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/utils/template.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(view, CVector _Rng, ccpt::uint _Count = ccpt::uint_<_Rng::size>,ccpt::uint _Offset = ccpt::uint_<0>, class = std::make_index_sequence<_Count::value>);
NGS_MPL_FUNCTION(view, CVector _Rng,ccpt::uint _Offset, size_t... _Index) < _Rng, ccpt::uint_<0>, _Offset, std::index_sequence<_Index...> > {
	using result_type = replace_template_parameters_t<_Rng>;
};
NGS_MPL_FUNCTION(view, CVector _Rng, ccpt::uint _Count,ccpt::uint _Offset, size_t... _Index) < _Rng, _Count,_Offset, std::index_sequence<_Index...> > {
	static_assert(_Offset::value + _Count::value <= _Rng::size, "out of range");
public:
	using result_type = replace_template_parameters_t<_Rng, typename _Rng::template at_c<_Index>...>;
};
template<CVector _Rng, ccpt::uint _Count = ccpt::uint_<_Rng::size>>
using view_t = typename view<_Rng, _Count>::result_type;

NGS_MPL_END
