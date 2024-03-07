#pragma once

#include "../basic.h"
#include "../context.h"
#include "../algorithm.h"
#include "./data.h"
#include "./vertex.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using indices_t = ::std::uint32_t;

template<contexts::vertex_buffer_descriptor... Buffers>
struct indices_vertex : vertex<Buffers...>
{
	NGS_MPL_ENVIRON2(indices_vertex, vertex<Buffers...>);
public:
	NGS_MPL_INHERIT_TYPE(vertex_struct_type, base_type);

	using indices_buffer_type = data_buffer<contexts::indices, indices_t>;
	using indices_sequence_callback_type = ::std::function<void(indices_buffer_type::range_type::iterator out, indices_t begin,::std::size_t count)>;
	using indices_sequence_count_callback_type = ::std::function<::std::size_t(::std::size_t count)>;

	indices_vertex(const vertex_info& info, const indices_sequence_callback_type& indices_sequence_callback, const indices_sequence_count_callback_type& indices_sequence_count_callback)
		: base_type(info)
		, _indices(info.usage)
		, _indices_sequence_callback(indices_sequence_callback)
		, _indices_sequence_count_callback(indices_sequence_count_callback)
	{}
	using base_type::operator=;

	void push_back(const ::std::ranges::sized_range auto& vertex_struct) requires ::std::convertible_to<::std::ranges::range_value_t<decltype(vertex_struct)>, vertex_struct_type>
	{
		auto size = _indices.data().size();
		_indices.data().resize(_indices_sequence_count_callback(::std::ranges::size(vertex_struct)));
		auto out = _indices.data().begin() + size;
		_indices_sequence_callback(out, base_type::size(), ::std::ranges::size(vertex_struct));

		for(auto&& vertex : vertex_struct)
		{
			base_type::push_back(vertex);
		}
	}

	void push_back(const vertex_struct_type& vertex_struct) { self_type::push_back(::std::initializer_list<vertex_struct_type>{vertex_struct}); }
	void push_back(const vertex_struct_type& v0, const vertex_struct_type& v1) { self_type::push_back(::std::initializer_list<vertex_struct_type>{v0,v1}); }
	void push_back(const vertex_struct_type& v0, const vertex_struct_type& v1, const vertex_struct_type& v2) { self_type::push_back(::std::initializer_list<vertex_struct_type>{v0,v1,v2}); }
	void push_back(const vertex_struct_type& v0, const vertex_struct_type& v1, const vertex_struct_type& v2, const vertex_struct_type& v3) { self_type::push_back(::std::initializer_list<vertex_struct_type>{v0,v1,v2,v3}); }

	void update(enums::usage usage)
	{
		base_type::update(usage);
		_indices.update(usage);
	}

	indices_buffer_type _indices;
	indices_sequence_callback_type _indices_sequence_callback;
	indices_sequence_count_callback_type _indices_sequence_count_callback;
};

NGS_LIB_MODULE_END