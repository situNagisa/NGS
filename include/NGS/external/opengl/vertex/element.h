#pragma once

#include "../basic.h"
#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class IndexType>
struct element : buffers::buffer<enums::buffer_target::element>, ::std::ranges::view_interface<element<IndexType>>
{
	NGS_MPL_ENVIRON(element);
public:
	using index_type = IndexType;

	constexpr element() = default;
	constexpr explicit element(::std::size_t count, enums::usage usage)
		: _usage(usage)
		, _data(count)
	{
		basic::bind(*this);
		buffers::allocate(*this, sizeof(index_type) * _data.size(), _usage);
	}

	void resize(::std::size_t size)
	{
		_data.resize(size);
		buffers::describe(*this, _data, _usage);
	}

	constexpr auto begin() { return _data.begin(); }
	constexpr auto begin() const { return _data.begin(); }
	constexpr auto end() { return _data.end(); }
	constexpr auto end() const { return _data.end(); }

private:
	enums::usage _usage{};
	buffers::unique_buffer<index_type> _data{};
};


NGS_LIB_MODULE_END