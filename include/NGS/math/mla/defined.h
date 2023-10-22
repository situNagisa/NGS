#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/basic.h"
#include "NGS/math/space.h"

#define NGS_MLA_BEGIN NGS_MATH_BEGIN namespace linear_algebra {
#define NGS_MLA_END } NGS_MATH_END

#define NGS_MLA_CONCEPT(concept_id, constant_id,convert_temp,ext)					\
template<class _Type = void>														\
concept concept_id = ext<_Type> && _##constant_id<convert_temp<_Type>>				\
//

#define NGS_MLA_CONCEPT_WITH_DEFINE(concept_id,constant_id,convert_temp,ext,...)\
template<class _Type>															\
static constexpr bool _##constant_id = __VA_ARGS__;								\
NGS_MLA_CONCEPT(concept_id,constant_id,convert_temp,ext);						\
template<class _Type>															\
struct constant_id : ngs::ccpt::bool_<(bool)concept_id<_Type>> {};				\
template<class _Type>															\
inline constexpr bool constant_id##_v = constant_id<_Type>::value				\
//

#define NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT(concept_id,constant_id,...)								\
NGS_MLA_CONCEPT_WITH_DEFINE(concept_id,constant_id,std::remove_cvref_t,ngs::ccpt::any,__VA_ARGS__)	\
//

#define NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(concept_id,constant_id,ext,...)			\
NGS_MLA_CONCEPT_WITH_DEFINE(concept_id,constant_id,std::remove_cvref_t,ext,__VA_ARGS__)	\
//

NGS_MLA_BEGIN
NGS_MLA_END

NGS_BEGIN

namespace mla = math::linear_algebra;

NGS_END
