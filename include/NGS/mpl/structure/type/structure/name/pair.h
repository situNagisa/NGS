#pragma once

#include "../structure.h"

NGS_STRUCTURE_TYPE_BEGIN

template<static_strings::static_string _Id>
using variable_id = ccpt::constant<decltype(_Id), _Id>;

template<static_strings::static_string _Id, class _Second>
using pair = boost::fusion::pair<variable_id<_Id>, _Second>;

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CVariableId = ccpt::Constant<_ObjectType> && static_strings::CStaticString<typename _ObjectType::value_type>;

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CPair = nboost::fusion::CPair<_ObjectType> && CVariableId<typename _ObjectType::first_type>;

NGS_STRUCTURE_TYPE_END
