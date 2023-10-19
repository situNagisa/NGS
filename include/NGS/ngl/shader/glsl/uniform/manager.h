#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/tuple.h"

NGL_BEGIN
/*
NGS_MPL_FUNCTION(uniform_manager, mpl::CVector _Tuples, class = std::make_index_sequence<_Tuples::size>);
NGS_MPL_FUNCTION(uniform_manager, CUniformTuple... _Tuples, size_t... _Index) < mpl::vector<_Tuples...>, std::index_sequence<_Index...> > {
public:
	using self_type = uniform_manager;

	template<static_strings::static_string _Id>
	using key_type = ccpt::constant<std::remove_cvref_t<decltype(_Id)>, _Id>;

	using struct_type = mpl::struct_<mpl::var_<typename _Tuples::element_type, _Tuples::element_count>...>;
	using memory_reinterpreter_type = MemoryReinterpreter<struct_type>;
	using container = mpl::map_<mpl::kv_pair_<key_type<_Tuples::name>, std::pair<ccpt::uint_<_Index>, _Tuples>>...>;
public:
	constexpr uniform_manager()
		: _memory(new byte[memory_reinterpreter_type::memory_size])
	{}
	constexpr ~uniform_manager() {
		delete[] _memory.Get(0);
	}

	template<static_strings::static_string _Id>
	constexpr auto Get() {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;

		return _memory.template Get<index_type::value>();
	}
	template<static_strings::static_string _Id>
	constexpr auto Get() const {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;

		return _memory.template Get<index_type::value>();
	}
	template<static_strings::static_string _Id>
	constexpr auto GetPointer() {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;
		auto wrapper = _memory.template Get<index_type::value>();
		using wrapper_type = decltype(wrapper);

		if constexpr (mla::CStandardMatrix<typename wrapper_type::element_type>) {
			return wrapper[0].data();
		}
		else if constexpr (mla::CStandardVector<typename wrapper_type::element_type>) {
			return wrapper[0].data();
		}
		else if constexpr (mla::CScalarExpression<typename wrapper_type::element_type>) {
			return wrapper.data();
		}
		else {
			return wrapper.data();
		}
	}

	friend constexpr std::string to_string(const self_type& manager) {
		std::string str;
		bool first = true;
		((str += (first ? "" : ", ") +
			to_string(_Tuples::name) + ": " + to_string(manager.Get<_Tuples::name>())
			, first = false), ...);
		return str;
	}
private:
	memory_reinterpreter_type _memory;
};

template<CUniformTuple... _Tuples>
using uniforms_ = uniform_manager<mpl::vector<_Tuples...>>;
*/

NGL_END
