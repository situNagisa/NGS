#pragma once

#include "./defined.h"

NGS_LIB_BEGIN
struct vector_tag {};

template<class _T>
struct tag_trait { using type = void; };

template<class _T>
using tag_trait_t = typename tag_trait<_T>::type;

template<class _T> requires requires { typename type_traits::object_t<_T>::nmla_type; }
struct tag_trait<_T> { using type = typename type_traits::object_t<_T>::nmla_type; };

struct basic_vector
{
	using nmla_type = vector_tag;
};

NGS_LIB_END