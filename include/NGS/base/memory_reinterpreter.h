#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/mpl/mpl.h"
#include "NGS/base/concepts.h"

NGS_BEGIN

template<CTemplateFrom<mpl::meta_struct> _Struct, class = std::make_index_sequence<mpl::spread_struct_t<_Struct>::count>>
class MemoryReinterpreter;

template<CTemplateFrom<mpl::meta_struct> _Struct, size_t ..._VarIndex>
class MemoryReinterpreter < _Struct, std::index_sequence< _VarIndex...>> {
public:
	using meta_struct_type = mpl::spread_struct_t<_Struct>;
	template<size_t _Index> using var = typename meta_struct_type::template var_at<_Index>;
	template<size_t _Index> using var_view = typename var<_Index>::view;
	template<size_t _Index> using var_container = typename var<_Index>::container;

	MemoryReinterpreter(void_ptr memory)
		: _memory(std::launder(reinterpret_cast<byte_ptr>(memory)))
	{}

	template<size_t _Index>
	var_view<_Index> Get() {
		return *std::launder(reinterpret_cast<var_container<_Index>*>(std::launder(_memory + meta_struct_type::vars[_Index].offset)));
	}

	void Set(var_view<_VarIndex>... vars) {
		(std::memcpy(Get<_VarIndex>().data(), vars.data(), var<_VarIndex>::size), ...);
	}
	void Set(var_container<_VarIndex>&&... var) { Set(var...); }

private:
	byte_ptr _memory = nullptr;
};

NGS_END
