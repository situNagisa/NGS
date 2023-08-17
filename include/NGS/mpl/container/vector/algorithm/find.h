#pragma once

#include "NGS/mpl/container/vector/vector.h"

NGS_MPL_BEGIN

NGS_mfunction(find_if, CVector _Rng, template<class...>class _Predicate, class = std::make_index_sequence<_Rng::size>);
NGS_mfunction(find_if, CVector _Rng, template<class>class _Predicate, size_t... _Index) < _Rng, _Predicate, std::index_sequence<_Index...> > {
private:
	consteval static int _GET_IS_SATISFY() {
		std::array<bool, _Rng::size> aim{ _Predicate<typename _Rng::template at_c<_Index>>::result_type::value... };
		for (size_t i = 0; i < aim.size(); i++)
		{
			if (aim[i])return i;
		}
		return -1;
	}
public:
	using result_type = ccpt::int_<_GET_IS_SATISFY()>;
};

template<CVector _Rng, template<class>class _Predicate>
using find_if_t = typename find_if<_Rng, _Predicate>::result_type;
template<CVector _Rng, template<class>class _Predicate>
constexpr auto find_if_v = find_if_t<_Rng, _Predicate>::value;

NGS_MPL_END
