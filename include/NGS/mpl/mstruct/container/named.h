#pragma once

#include "./storage.h"
#include "../named.h"
#include "./fields.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<layout::align auto Align, nameds::named_field... Fields>
struct named_struct : storage<Align, nameds::named_pair_field_t<Fields>...>
{
	NGS_MPL_ENVIRON2(named_struct, storage<Align, nameds::named_pair_field_t<Fields>...>);
public:
	using named_fields_type = ::boost::fusion::vector<Fields...>;

	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END