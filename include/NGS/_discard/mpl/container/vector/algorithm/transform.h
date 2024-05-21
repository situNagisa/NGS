#pragma once

#include "NGS/mpl/container/vector/vector.h"
#include "NGS/mpl/utils/template.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(transform, class _Rng, template<class...>class _Transformer, class = std::make_index_sequence<_Rng::size>);
/**
 * \brief Transform a vector into another vector using a transformer.
 * 
 * \tparam _Transformer transform(range[i]) -> result_type
 */
NGS_MPL_FUNCTION(_vector_transform_1, CVector _Rng, template<class>class _Transformer, size_t... _Index) {
	using result_type = replace_template_parameters_t<_Rng, typename _Transformer<typename _Rng::template at_c<_Index>>::result_type...>;
};
/**
 * \tparam _Transformer transform(range,uint_<i>) -> result_type
 */
NGS_MPL_FUNCTION(_vector_transform_2, CVector _Rng, template<class,class>class _Transformer, size_t... _Index) {
	using result_type = replace_template_parameters_t<_Rng, typename _Transformer<_Rng,ccpt::uint_<_Index>>::result_type...>;
};

NGS_MPL_FUNCTION(transform, CVector _Rng, template<class...>class _Transformer, size_t... _Index) < _Rng, _Transformer, std::index_sequence<_Index...> > {
	using result_type = typename std::conditional_t<
		ccpt::FunctorParameterTest<_Transformer, void, void>,
		_vector_transform_2<_Rng, _Transformer, _Index...>,
		_vector_transform_1<_Rng, _Transformer, _Index...>>::result_type;
};

template<CVector _Rng, template<class...>class _Transformer>
using transform_t = typename transform<_Rng, _Transformer>::result_type;

NGS_MPL_END
