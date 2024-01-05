#pragma once

#include "NGS/math/mla/defined.h"
#include "NGS/math/mla/scalar/traits.h"

NGS_MLA_BEGIN

/**
 * @brief ScalarUnaryFunctor concept
 *
 * @property type argument_type
 * @property type result_type
 * @property static function result_type apply(argument_type)
*/
template<class  T>
concept CScalarUnaryFunctor = requires(typename T::argument_type argument) {
	typename T::argument_type;
	typename T::result_type;

	{ T::apply(argument) } -> std::convertible_to<typename T::result_type>;
};

template<class  _ElementType>
struct NGS_DLL_API ScalarUnaryFunctor {
protected:
	using self_type = ScalarUnaryFunctor;
public:
	using argument_type = typename scalar_traits<_ElementType>::const_reference;
	using result_type = typename scalar_traits<_ElementType>::real_type;

	constexpr static result_type apply(argument_type x) { return x; }
};
NGS_CCPT_VERIFY(CScalarUnaryFunctor, ScalarUnaryFunctor<int>);

NGS_MLA_END
