#pragma once

#include "NGS/mpl/defined.h"
#include "NGS/mpl/container/set/set.h"
#include "NGS/mpl/container/map/key_value_pair.h"
#include "NGS/mpl/container/set/algorithm/find_if.h"

NGS_MPL_BEGIN

NGS_MPL_FUNCTION(map, template<class...>class _Equal = equal, CKeyValuePair... _KVPair) : public set<_Equal, _KVPair...>{
	NGS_MPL_ENVIRON(map);
public:
	template<class _With>
	struct high_order_predicate {
		template<class _Type>
		using predicate_type = _Equal<_Type, kv_pair_<_With, void>>;
	};
public:
	template<class _Key>
	constexpr static auto _GET_INDEX_OF_KEY() {
		using high_p = high_order_predicate<_Key>;
		using result_type = find_if_t<base_type, high_order_predicate<_Key>::template predicate_type>;
		//static_assert(find_if_t<base_type, high_p::template predicate_type>::value != -1, "The key is not found in the map.");
		return ::ngs::declval<result_type>();
	}

	template<ccpt::integral _Index>
	constexpr static auto _GET_VALUE_TYPE() {
		if constexpr (_Index::value == -1) {
			static_assert(_Index::value != -1, "The key is not found in the map.");
			return void();
		}
		else {
			return ::ngs::declval<typename base_type::template element_at_c<static_cast<size_t>(_Index::value)>::value_type>();
		}
	}
public:
	template<class _Key>
	NGS_MPL_TYPE index_of = decltype(_GET_INDEX_OF_KEY<_Key>());
	template<class _Key>
	NGS_MPL_TYPE value_type = decltype(_GET_VALUE_TYPE<index_of<_Key>>());
};

template<CKeyValuePair... _KVPair>
using map_ = map<equal, _KVPair...>;

NGS_MPL_END
