#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/container/vector/algorithm/push.h"
#include "NGS/mpl/utils/template.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(filter, class _Rng, template<class...>class _Predicate, class = std::make_index_sequence<_Rng::size>);

template<CVector _Rng, template<class...>class _Predicate>
using filter_t = typename filter<_Rng, _Predicate>::result_type;

NGS_MPL_FUNCTION(_vector_filter_2, CVector _Rng, template<class...>class _Predicate, size_t... _Index){
public:
	constexpr static std::array<bool,_Rng::size> _result = { _Predicate<_Rng,ccpt::uint_<_Index>>::result_type::value... };
	constexpr static size_t _satisfy_count = (_result[_Index] + ...);
	constexpr static std::array<size_t,_satisfy_count> _satisfy = [] {
			std::array<size_t, _satisfy_count> result{};
			size_t count = 0;
			for (size_t i = 0; i < _result.size(); i++)
			{
				if (!_result[i])continue;
				result[count] = i;
				count++;
			}
			return result;
		}();

public:
	using result_type = decltype([]<size_t... _I>(std::index_sequence<_I...>){
		return replace_template_parameters_t<_Rng,typename _Rng::template at_c<_satisfy[_I]>...>();
		}(std::make_index_sequence<_satisfy_count>()));
};
NGS_MPL_FUNCTION(_vector_filter_1, CVector _Rng, template<class...>class _Predicate, size_t... _Index){
	template<class _Sequence, class _I>
	struct predicate_type {
		using result_type = typename _Predicate<typename _Sequence::template at<_I>>::result_type;
	};
	using result_type = typename _vector_filter_2<_Rng, predicate_type,_Index...>::result_type;
};

NGS_MPL_FUNCTION(filter, CVector _Rng, template<class...>class _Predicate, size_t... _Index) < _Rng, _Predicate, std::index_sequence<_Index...> > {
	NGS_MPL_TYPE result_type = typename std::conditional_t<
		ccpt::FunctorParameterTest<_Predicate, void, void>,
		_vector_filter_2<_Rng, _Predicate, _Index...>,
		_vector_filter_1<_Rng, _Predicate, _Index...>>::result_type;
};


NGS_MPL_END
