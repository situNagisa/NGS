#pragma once

#include "./defined.h"

NGS_ALLOCATOR_BEGIN

using id_t = int;
inline constexpr id_t invalid_id = static_cast<id_t>(-1);

template<size_t _Count>
class NGS_DLL_API id {
public:
	using bit_set_type = bits::bit_set<_Count>;
public:
	id_t allocate() {
		for (id_t i = 0; i < bit_set_type::bit_count; i++) {
			if (_bit_set[i])continue;
			_bit_set[i] = true;
			return i;
		}
		return invalid_id;
	}
	void free(const id_t& number) { _bit_set[number] = false; }
	bool is_allocated(const id_t& number) const { return _bit_set[number]; }

	bool is_full()const { return _bit_set.count() == bit_set_type::bit_count; }
private:

private:
	bit_set_type _bit_set{};
};

NGS_ALLOCATOR_END