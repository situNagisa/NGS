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
	
private:
	template<static_string _Id>
	static constexpr auto _get_uniform_type() {
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;
		using tuple_type = typename value_type::second_type;

		if constexpr (tuple_type::element_count == 1) {
			if constexpr (tuple_type::dimension == 1) {
				//返回引用有点麻烦，不写成auto&的话自动推导推导为值类型，写成引用对于其他情况会造成悬垂引用
				using return_type = typename tuple_type::original_type;
				return declval<return_type>();
			}
			else {
				if constexpr (map::is_matrix_dimension<tuple_type::dimension>) {
					constexpr auto size = map::convert_to_matrix_row_col<tuple_type::dimension>;
					using return_type = std::span<typename tuple_type::original_type, size.x* size.y>;
					return declval<return_type>();
				}
				else {
					using return_type = std::span<typename tuple_type::original_type, tuple_type::dimension>;
					return declval<return_type>();
				}
			}
		}
		else {
			using return_type = std::span<typename tuple_type::element_type, tuple_type::element_count>;
			return declval<return_type>();
		}
	}
public:
	template<static_string _Id>
	using uniform_type = decltype(_get_uniform_type<_Id>());
public:
	constexpr uniform_manager()
		: _memory(new byte[memory_reinterpreter_type::memory_size])
	{}
	constexpr ~uniform_manager() {
		delete[] _memory.Get(0);
	}
	
	template<static_string _Id>
	constexpr auto Get() {
		//与uniform_tuple的耦合度有点高，待优化
		using value_type = typename container::template value_type<key_type<_Id>>;
		using index_type = typename value_type::first_type;
		using tuple_type = typename value_type::second_type;
		using return_type = uniform_type<_Id>;

		if constexpr (tuple_type::element_count == 1) {
			if constexpr (tuple_type::dimension == 1) {
				//返回引用有点麻烦，不写成auto&的话自动推导推导为值类型，写成引用对于其他情况会造成悬垂引用
				//using return_type = typename tuple_type::original_type;
				return static_cast<return_type*>(_memory.template Get<index_type::value>());
			}
			else {
				if constexpr (map::is_matrix_dimension<tuple_type::dimension>) {
					constexpr auto size = map::convert_to_matrix_row_col<tuple_type::dimension>;
					//using return_type = std::span<typename tuple_type::original_type, size.x* size.y>;
					return return_type{ *_memory.template Get<index_type::value>() };
				}
				else {
					//using return_type = std::span<typename tuple_type::original_type, tuple_type::dimension>;
					return return_type{ *_memory.template Get<index_type::value>() };
				}
			}
		}
		else {
			//using return_type = std::span<typename tuple_type::element_type, tuple_type::element_count>;
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
