#pragma once

#include "./defined.h"

NGS_STL_ITERATOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept is_config = requires
{
	typename _O::iterator_category;
	typename _O::iterator_concept;
	typename _O::value_type;
	typename _O::reference;
	typename _O::pointer;
	typename _O::difference_type;
};

template<
	class _IteratorCategory = type_traits::na,
	class _IteratorConcept = type_traits::na,
	class _ValueType = type_traits::na,
	class _Reference = type_traits::na,
	class _Pointer = type_traits::na,
	class _DifferenceType = type_traits::na
>
struct config;

using default_config = config<>;

template<
	class _IteratorCategory,
	class _IteratorConcept,
	class _ValueType,
	class _Reference,
	class _Pointer,
	class _DifferenceType
>
struct config
{
protected:
	using self_type = config;
public:
	using iterator_category = _IteratorCategory;
	using iterator_concept = _IteratorConcept;
	using value_type = _ValueType;
	using reference = _Reference;
	using pointer = _Pointer;
	using difference_type = _DifferenceType;

	template<class _T>
	using set_iterator_category = config<_T, iterator_concept, value_type, reference, pointer, difference_type>;

	template<class _T>
	using set_iterator_concept = config<iterator_category, _T, value_type, reference, pointer, difference_type>;

	template<class _T>
	using set_value_type = config<iterator_category, iterator_concept, _T, reference, pointer, difference_type>;

	template<class _T>
	using set_reference = config<iterator_category, iterator_concept, value_type, _T, pointer, difference_type>;

	template<class _T>
	using set_pointer = config<iterator_category, iterator_concept, value_type, reference, _T, difference_type>;

	template<class _T>
	using set_difference_type = config<iterator_category, iterator_concept, value_type, reference, pointer, _T>;
};

#define NGS_STL_ITERATOR_CONFIG_VALUE_OR2(type_name,config_type,...)						\
using type_name = NGS_ mpl::options::value_or<typename config_type::type_name, __VA_ARGS__>	\
//
#define NGS_STL_ITERATOR_CONFIG_VALUE_OR(type_name,...) NGS_STL_ITERATOR_CONFIG_VALUE_OR2(type_name, base_type, __VA_ARGS__)

NGS_STL_ITERATOR_END