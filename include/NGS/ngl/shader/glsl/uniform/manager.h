#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/tuple.h"

NGL_BEGIN

NGS_mfunction(uniform_manager, mpl::CVector _Tuples, class = std::make_index_sequence<_Tuples::size>);
NGS_mfunction(uniform_manager, CUniformTuple... _Tuples, size_t... _Index) < mpl::vector<_Tuples...>, std::index_sequence<_Index...> > {
public:
	using struct_type = mpl::struct_<mpl::var_<typename _Tuples::element_type, _Tuples::element_count>...>;
	using memory_reinterpreter_type = MemoryReinterpreter<struct_type>;
	using container = mpl::map_<mpl::kv_pair_<ccpt::constant<decltype(_Tuples::name), _Tuples::name>, std::pair<ccpt::uint_<_Index>, _Tuples>>...>;
public:
	constexpr uniform_manager()
		: _memory(new byte[memory_reinterpreter_type::memory_size])
	{}
	constexpr ~uniform_manager() {
		delete[] _memory.Get(0);
	}
	template<static_string _Id>
	constexpr auto Get() {
		using value_type = typename container::template value_type<ccpt::constant<decltype(_Id), _Id>>;
		static_assert(!std::same_as<value_type, void>);
		using index_type = typename value_type::first_type;
		using return_type = typename mpl::variable_trait<typename value_type::second_type>::view_type;
		return return_type(_memory.template Get<index_type::value>(), value_type::second_type::element_count);
	}
private:
	memory_reinterpreter_type _memory;
};

template<CUniformTuple... _Tuples>
using uniforms_ = uniform_manager<mpl::vector<_Tuples...>>;

NGL_END
