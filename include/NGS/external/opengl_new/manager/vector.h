#pragma once

#include "./index.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<
	class Indexer,
	NGS_EXTERNAL_OPENGL_BASIC_REFLECT_NS::buffer_indices Index,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_descriptor... Buffers
> requires NGS_EXTERNAL_OPENGL_INDEXER_NS::topology_indexer<Indexer, Index>
struct vector_index_manager : index_manager<
	NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_group<NGS_EXTERNAL_OPENGL_BUFFER_NS::vertex_buffer<::std::vector<Buffers>>...>,
	NGS_EXTERNAL_OPENGL_BUFFER_NS::indices_buffer<Indexer, ::std::vector<Index>>
>
{
	NGS_MPL_ENVIRON(vector_index_manager);
public:
	vector_index_manager(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices, bool normalized = false,::std::size_t vertex_count = 0)
		: base_type(
			NGS_EXTERNAL_OPENGL_BUFFER_NS::make_vector_vertex_group<Buffers...>(vertex,vertex_count),
			NGS_EXTERNAL_OPENGL_BUFFER_NS::make_vector_indices_buffer<Indexer,Index>(indices, (vertex_count == 0 ? 0 : Indexer::indices_count_of(vertex_count))),
			normalized
		)
		, _usage{vertex,indices}
	{}

	void describe(NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex, NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices)
	{
		_usage = {vertex,indices};
		self_type::describe();
	}
	void describe()
	{
		base_type::describe(_usage.vertex, _usage.indices);
	}

	void resize(::std::size_t vertex_count)
	{
		base_type::group().for_each_buffer([vertex_count](auto& buffer)
			{
				buffer.data().resize(vertex_count);
			});
		base_type::index().data().resize(base_type::index().data().size() + typename base_type::index_buffer_type::indexer_type::indices_count_of(vertex_count));

		self_type::describe();
	}
	decltype(auto) push_back_range(::std::ranges::sized_range auto&& vertex_range)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>, ::std::ranges::iterator_t<typename base_type::group_type>>
	{
		auto current_size = static_cast<NGS_EXTERNAL_OPENGL_BUFFER_NS::buffer_value_t<typename base_type::index_buffer_type>>(::std::ranges::size(base_type::group()));
		auto current_index_size = ::std::ranges::size(base_type::index().data());
		self_type::resize(current_size + ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vertex_range)));
		base_type::copy_from(NGS_PP_PERFECT_FORWARD(vertex_range), current_size, current_size, current_index_size);
	}

	decltype(auto) push_back_range(::std::initializer_list<typename base_type::vertex_type>&& vertex_range)
	{
		return self_type::push_back_range(vertex_range);
	}


	struct
	{
		NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage vertex;
		NGS_EXTERNAL_OPENGL_BASIC_ENUM_NS::usage indices;
	}_usage{};
};

NGS_LIB_MODULE_END