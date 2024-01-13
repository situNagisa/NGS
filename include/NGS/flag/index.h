#pragma once

#include "./basic.h"
#include "./enum.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _ValueType>
struct index_flag : ::std::conditional_t<::std::is_enum_v<_ValueType>, enum_flag<_ValueType>, flag<_ValueType>>
{
	NGS_MPL_ENVIRON(index_flag);
public:
	NGS_MPL_INHERIT_TYPE(value_type, base_type);

	using base_type::base_type;


};

NGS_LIB_END