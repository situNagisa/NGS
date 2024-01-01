#pragma once

#include "../defined.h"

NGS_STATIC_FUNCTIONAL_BEGIN
namespace detail
{
struct reference_tag {};
}

template<class _T, class _O = type_traits::object_t<_T>>
concept is_reference = requires
{
	typename _O::type_category;
	std::derived_from<typename _O::type_category, detail::reference_tag>;
};

NGS_STATIC_FUNCTIONAL_END
