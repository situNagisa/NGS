#pragma once

#include "./defined.h"

#define NGS_TVM_REGISTER(mapper,value_type_)								\
namespace mapper{															\
using value_type = value_type_;												\
template<class> constexpr value_type value = {};							\
template<value_type> struct type_map;										\
template<value_type _Value> using type = typename type_map<_Value>::type;	\
}																			\
//

#define NGS_TVM_INSERT(mapper,type_,value_)																\
template<> constexpr mapper::value_type mapper::value<type_> = static_cast<mapper::value_type>(value_);	\
template<> struct mapper::type_map<static_cast<mapper::value_type>(value_)> { using type = type_; };	\
//

NGS_LIB_BEGIN

namespace detail
{
	template<class, class, class... _Types>
	struct sequence_mapper;

	template<class _Tag, size_t... _Indexes, class... _Types>
	struct sequence_mapper<_Tag, std::index_sequence<_Indexes...>, _Types...>
	{
	private:
		using sequence_type = ::boost::fusion::vector<_Types...>;
		using map_type = ::boost::fusion::map<::boost::fusion::pair<_Types, ccpt::uint_<_Indexes>>...>;
	public:
		template<size_t _Index> using type = typename ::boost::fusion::result_of::value_at_c<sequence_type, _Index>::type;
		template<class _Type> constexpr static size_t value = type_traits::object_t<typename ::boost::fusion::result_of::at_key<map_type, _Type>::type>::value;
	};
}

template<class _Tag, class... _Types>
using sequence_mapper = detail::sequence_mapper<_Tag, std::make_index_sequence<sizeof...(_Types)>, _Types...>;

NGS_LIB_END

#define NGS_TVM_SEQUENCE(mapper,...)									\
struct _mapper##_tag;													\
using mapper = NGS_ tvm::sequence_mapper<_mapper##_tag, __VA_ARGS__>;	\
//