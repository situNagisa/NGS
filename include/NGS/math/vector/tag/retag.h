#pragma once

#include "./basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Tag, class _Base = void>
struct retag : _Base
{
	using linear_algebra_category_type = _Tag;
	using base_type = _Base;
	using self_type = retag;

	using base_type::base_type;
	using base_type::operator=;
};

template<class _Tag>
struct retag<_Tag, void>
{
	using linear_algebra_category_type = _Tag;
	using self_type = retag;
};

NGS_LIB_MODULE_END