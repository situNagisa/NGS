#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct placeholder_tag {};
}

template<class _T>
concept is_placeholder = ccpt::constant<_T, index_t>&& ::std::derived_from<typename type_traits::object_t<_T>::ngs_functional_parameter_packet_placeholder_tag, _detail::placeholder_tag>;

NGS_LIB_MODULE_END