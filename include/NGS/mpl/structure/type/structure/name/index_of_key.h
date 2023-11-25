#pragma once

#include "./name_struct.h"

NGS_STRUCTURE_TYPE_BEGIN

template<CNamedStruct _Struct, CVariableId _Id>
struct index_of_key {
	using type = typename boost::fusion::result_of::value_at_key<typename _Struct::map_type, _Id>::type;
};

template<CNamedStruct _Struct, statics::strings::string _Id>
struct index_of_key_c {
	using type = typename index_of_key<_Struct, variable_id<_Id>>::type;
};

NGS_STRUCTURE_TYPE_END
