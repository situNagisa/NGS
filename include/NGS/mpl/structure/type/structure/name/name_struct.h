#pragma once

#include "../structure.h"
#include "./pair.h"

NGS_LIB_MODULE_BEGIN

template<class _Type, class _ObjectType = std::remove_reference_t<_Type>>
concept CNamedStruct = CStructure<_ObjectType> && requires(_ObjectType obj, const _ObjectType obj_cst) {
	requires external::nboost::fusion::CMap<typename _ObjectType::map_type>;
};

template<class...>
struct _name_struct;

template<layout::CAlign _Align, size_t... _Index, CPair... _Pairs>
struct _name_struct<_Align, std::index_sequence<_Index...>, _Pairs...> :
	structure<_Align, typename _Pairs::second_type...>
{
	NGS_MPL_ENVIRON(_name_struct);
public:
	using map_type = boost::fusion::map <
		boost::fusion::pair<typename _Pairs::first_type, ccpt::uint_<_Index>>...
	>;
public:
	using base_type::get;
	template<size_t __Index>
	constexpr auto&& get() {
		return base_type::template get<__Index>();
	}
	template<size_t __Index>
	constexpr auto&& get()const {
		return base_type::template get<__Index>();
	}
	template<statics::strings::string _Id>
	constexpr auto&& get() {
		return self_type::template get<boost::fusion::result_of::value_at_key<map_type, variable_id<_Id>>::type::value>();
	}
	template<statics::strings::string _Id>
	constexpr auto&& get()const {
		return self_type::template get<boost::fusion::result_of::value_at_key<map_type, variable_id<_Id>>::type::value>();
	}
};

template<layout::CAlign _Align, CPair... _Pairs>
using name_struct = _name_struct<_Align, std::make_index_sequence<sizeof...(_Pairs)>, _Pairs...>;

NGS_LIB_MODULE_END
