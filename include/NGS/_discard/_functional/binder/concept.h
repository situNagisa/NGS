#pragma once

#include "../param.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	struct binder_tag {};
}

template<class _T, class _O = type_traits::object_t<_T>>
concept is_binder = is_param<_T> && requires
{
	typename _O::type_category;
	std::derived_from<typename _O::type_category, _detail::binder_tag>;
};

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(is_binder);
