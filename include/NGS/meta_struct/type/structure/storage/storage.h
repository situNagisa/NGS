#pragma once

#include "./concept.h"

NGS_META_STRUCT_TYPE_BEGIN

template<CStructureDescribe _Describe>
struct alignas(_Describe::align) struct_storage {
	using describe_type = _Describe;

	constexpr struct_storage() = default;

	template<class _Type>
		requires (sizeof(_Type) == describe_type::size)
	constexpr struct_storage& operator=(const _Type& obj) {
		std::memcpy(data, &obj, describe_type::size);
		return *this;
	}

	template<size_t _Index>
	constexpr auto&& get() {
		constexpr auto variables = describe_type::GET_VARIABLES();
		using variable_type = typename describe_type::template variable_at<_Index>;
		return *(reinterpret_cast<typename variable_type::storage_type*>(data + variables[_Index].offset));
	}
	template<size_t _Index>
	constexpr auto&& get()const {
		constexpr auto variables = describe_type::GET_VARIABLES();
		using variable_type = typename describe_type::template variable_at<_Index>;
		return *(reinterpret_cast<const typename variable_type::storage_type*>(data + variables[_Index].offset));
	}

	byte data[describe_type::size]{};
};

NGS_META_STRUCT_TYPE_END
