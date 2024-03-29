﻿#pragma once

#include "../defined.h"
#include "../../variable/concept.h"
#include "../../variable/dynamic_data.h"

NGS_LIB_MODULE_BEGIN

template<class _Type = void, class _ObjectType = std::remove_reference_t<_Type>>
concept CStructureDescribe = requires() {
	{ _ObjectType::variable_count } -> ::std::convertible_to<size_t>;
	{ _ObjectType::size } -> ::std::convertible_to<size_t>;
	{ _ObjectType::align } -> ::std::convertible_to<size_t>;
	{ _ObjectType::get_variables() };// -> ::std::convertible_to<::std::span<variable_dynamic_data>>;

		requires ((_ObjectType::variable_count == 0) || (_ObjectType::variable_count > 0 && CVariable<typename _ObjectType::template variable_at<0>>));
		requires layout::CAlign<typename _ObjectType::align_type>;
	//requires mpl::CVector<typename _ObjectType::variable_types>;
	typename _ObjectType::variable_types;
};

NGS_LIB_MODULE_END
