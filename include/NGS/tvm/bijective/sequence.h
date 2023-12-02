#pragma once

#include "../defined.h"

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