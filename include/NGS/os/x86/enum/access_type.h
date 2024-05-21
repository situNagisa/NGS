#pragma once

#include "./privilege.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class access_type
{
	read_only = 0,
	read_write = 1,
};

constexpr auto operator<=>(access_type left, access_type right)
{
	return static_cast<::std::underlying_type_t<access_type>>(left) <=> static_cast<::std::underlying_type_t<access_type>>(right);
}

constexpr auto high(access_type left, access_type right) { return ::std::max(left, right); }
constexpr auto low(access_type left, access_type right) { return ::std::min(left, right); }

constexpr auto access_privilege(bool write_protect, page_privilege pde_privilege,access_type pde_access, page_privilege pte_privilege, access_type pte_access)
{
	auto privilege = NGS_LIB_MODULE_NAME::high(pde_privilege, pte_privilege);
	auto access = NGS_LIB_MODULE_NAME::low(pde_access, pte_access);

	if(privilege == page_privilege::supervisor && !write_protect)
		return ::std::make_pair(privilege, access_type::read_write);

	return ::std::make_pair(privilege, access);
}

NGS_LIB_MODULE_END