#pragma once

#include "NGS/mla/defined.h"
#include "NGS/mla/scalar/traits.h"

NGS_MLA_BEGIN

/**
 * @brief CScalarBinaryFunctor concept
 *
 * @property type argument_type1
 * @property type argument_type2
 * @property type result_type
 * @property static function result_type apply(argument_type)
*/
template<class T>
concept CScalarBinaryFunctor = requires(typename T::argument_type1 argument1, typename T::argument_type2 argument2) {
	typename T::argument_type1;
	typename T::argument_type2;
	typename T::result_type;

	{ T::apply(argument1, argument2) } -> std::convertible_to<typename T::result_type>;
};

template<class _ElementType1, class _ElementType2>
struct ScalarBinaryFunctor {
protected:
	using self_type = ScalarBinaryFunctor<_ElementType1, _ElementType2>;
public:
	using argument_type1 = typename scalar_traits<_ElementType1>::const_reference;
	using argument_type2 = typename scalar_traits<_ElementType2>::const_reference;
	using result_type = mpl::promote_t<_ElementType1, _ElementType2>;

	constexpr static result_type apply(argument_type1 x, argument_type2 y) {
		//static_assert(false, "ScalarBinaryFunctor::apply is not implemented");
		return result_type();
	}
};

template<class _ElementType1, class _ElementType2>
struct ScalarBinaryAssignFunctor {
protected:
	using self_type = ScalarBinaryAssignFunctor<_ElementType1, _ElementType2>;
public:
	using argument_type1 = typename scalar_traits<_ElementType1>::reference;
	using argument_type2 = typename scalar_traits<_ElementType2>::const_reference;
	using result_type = argument_type1;

	constexpr static result_type apply(argument_type1 x, argument_type2 y) {
		//static_assert(false, "ScalarBinaryFunctor::apply is not implemented");
		return result_type();
	}
};

NGS_CCPT_VERIFY(CScalarBinaryFunctor, ScalarBinaryFunctor<int, float>);
NGS_CCPT_VERIFY(CScalarBinaryFunctor, ScalarBinaryAssignFunctor<int, float>);

NGS_MLA_END
