#pragma once

#include "./name_struct.h"
#include "./index_of_key.h"

NGS_STRUCTURE_TYPE_BEGIN

template<CNamedStruct _Struct, CVariableId _Id>
struct variable_at_key {
	using type = typename _Struct::template variable_at<index_of_key<_Struct, _Id>::type::value>;
};

template<CNamedStruct _Struct, statics::strings::string _Id>
struct variable_at_key_c {
	using type = typename variable_at_key<_Struct, variable_id<_Id>>::type;
};

NGS_STRUCTURE_TYPE_END
