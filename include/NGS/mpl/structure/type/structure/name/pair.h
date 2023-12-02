#pragma once

#include "../structure.h"
#include "../defined.h"

NGS_LIB_MODULE_BEGIN

template<statics::strings::string _Id>
using variable_id = ccpt::constant_<decltype(_Id), _Id>;

template<statics::strings::string _Id, class _Second>
using pair = boost::fusion::pair<variable_id<_Id>, _Second>;

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CVariableId = ccpt::constant<_ObjectType> && statics::strings::CString<typename _ObjectType::value_type>;

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CPair = nboost::fusion::CPair<_ObjectType> && CVariableId<typename _ObjectType::first_type>;

NGS_LIB_MODULE_END
