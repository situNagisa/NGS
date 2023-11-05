#pragma once

#include "../param.h"

NGS_STATIC_FUNCTIONAL_BEGIN
namespace detail
{
struct binder_tag {};
}

template<class _T, class _O = type_traits::object_t<_T>>
concept is_binder = is_param<_T> && requires
{
	typename _O::type_category;
	std::derived_from<typename _O::type_category, detail::binder_tag>;
};

NGS_STATIC_FUNCTIONAL_END
