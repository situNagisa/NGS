#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/functor/find_if.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(_vector_find_if_2, CVector _Rng, template<class...>class _Predicate){
private:
	template<size_t... _Index>
	consteval static int _GET_IS_SATISFY(std::index_sequence<_Index...>) {
		std::array<bool, _Rng::size> aim{ _Predicate<_Rng,ccpt::uint_<_Index>>::result_type::value... };
		for (size_t i = 0; i < aim.size(); i++)
		{
			if (aim[i])return static_cast<int>(i);
		}
		return -1;
	}
public:
	using result_type = ccpt::int_<_GET_IS_SATISFY(std::make_index_sequence<_Rng::size>())>;
};
NGS_MPL_FUNCTION(_vector_find_if_1, CVector _Rng, template<class...>class _Predicate){
private:
	template<class _R, class _I>
	struct predicate_type {
		using result_type = typename _Predicate<typename _R::template at<_I>>::result_type;
	};
public:
	using result_type = typename _vector_find_if_2<_Rng, predicate_type>::result_type;
};

NGS_MPL_FUNCTION(find_if, CVector _Rng, template<class...>class _Predicate) < _Rng, _Predicate > {
	using result_type = typename std::conditional_t<
		ccpt::FunctorParameterTest<_Predicate, void, void>,
		_vector_find_if_2<_Rng, _Predicate>,
		_vector_find_if_1<_Rng, _Predicate>>::result_type;
};

NGS_MPL_END
