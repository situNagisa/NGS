#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/shader/glsl/uniform/tuple.h"

NGL_BEGIN

NGS_mfunction(uniform_manager, mpl::CVector _Tuples, class = std::make_index_sequence<_Tuples::size>);
NGS_mfunction(uniform_manager, CUniformTuple... _Tuples, size_t... _Index) < mpl::vector<_Tuples...>, std::index_sequence<_Index...> > {
public:
	template<static_string _Id>
	using key_type = ccpt::constant<std::remove_cvref_t<decltype(_Id)>, _Id>;

	using struct_type = mpl::struct_<mpl::var_<typename _Tuples::element_type, _Tuples::element_count>...>;
	using memory_reinterpreter_type = MemoryReinterpreter<struct_type>;
	using container = mpl::map_<mpl::kv_pair_<key_type<_Tuples::name>,std::pair<ccpt::uint_<_Index>, _Tuples>>...>;
public:
	constexpr uniform_manager()
		: _memory(new byte[memory_reinterpreter_type::memory_size])
	{}
	constexpr ~uniform_manager() {
		delete[] _memory.Get(0);
	}
	template<static_string _Id>
	constexpr auto Get() {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;
		using tuple_type = typename value_type::second_type;
		if constexpr (tuple_type::element_count == 1) {
			constexpr auto size = map::convert_to_matrix_row_col<tuple_type::dimension>;
			using return_type = std::span<typename tuple_type::original_type, size.x * size.y>;
			return return_type{ *_memory.template Get<index_type::value>() };
		}
		else {
			using return_type = std::span<typename tuple_type::element_type, tuple_type::element_count>;
			return return_type{ _memory.template Get<index_type::value>(), value_type::second_type::element_count };
		}
		
	}
	template<static_string _Id>
	constexpr auto GetPointer() {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;
		using tuple_type = typename value_type::second_type;
		using return_type = typename tuple_type::original_type*;
		return std::launder(reinterpret_cast<return_type>(_memory.template Get<index_type::value>()));
	}
private:
	memory_reinterpreter_type _memory;
};

template<CUniformTuple... _Tuples>
using uniforms_ = uniform_manager<mpl::vector<_Tuples...>>;

NGL_END
