#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _T>
	constexpr bool is_pack_impl()
	{
		using object_type = type_traits::object_t<_T>;
		if constexpr (!requires
		{
			{object_type::count} -> std::convertible_to<size_t>;
			requires cpt::is_template<typename object_type::sequence_type>;
		})
		{
			return false;
		}
		else
		{
			if constexpr (!object_type::count)
			{
				return true;
			}
			else
			{
				return true;
			}
		}
	}
}

template<class _T>
concept is_packer = _detail::is_pack_impl<_T>();

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(is_packer);