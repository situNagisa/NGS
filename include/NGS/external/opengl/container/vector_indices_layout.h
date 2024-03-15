#pragma once

#include "../reflect.h"
#include "../enum.h"
#include "./indices_layout.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<
	valid_fundamental IndexType,
	indices::indices_drawer<IndexType,::std::ranges::iterator_t<::std::vector<IndexType>>> IndicesDrawer,
	contexts::vertex_buffer_descriptor... BufferDescriptor
>
struct vector_indices_layout : indices_layout<policy::layout<policy::vertex_buffer<::std::vector<BufferDescriptor>>...>,policy::indices_buffer<::std::vector<IndexType>,IndicesDrawer>>
{
	NGS_MPL_ENVIRON2(vector_indices_layout, indices_layout<policy::layout<policy::vertex_buffer<::std::vector<BufferDescriptor>>...>, policy::indices_buffer<::std::vector<IndexType>, IndicesDrawer>>);

public:
	vector_indices_layout(bool normalized, enums::usage vertex_usage, enums::usage indices_usage,::std::size_t vertex_count)
		: base_type(
			{ normalized, vertex_usage, vertex_count }, 
			{ indices_usage, (vertex_count == 0) ? 0 : typename base_type::indices_buffer_type::indices_drawer_type::indices_count_of(vertex_count) }
		)
		, _vertex_usage(vertex_usage)
		, _indices_usage(indices_usage)
	{}
	vector_indices_layout(bool normalize, enums::usage usage, ::std::size_t vertex_count)
		: self_type(normalize, usage, usage, vertex_count)
	{}
	vector_indices_layout(bool normalized, enums::usage vertex_usage, enums::usage indices_usage)
		: self_type(normalized, vertex_usage, indices_usage, 0)
	{}
	vector_indices_layout(bool normalize, enums::usage usage)
		: self_type(normalize, usage, usage, 0)
	{}

	void describe(enums::usage vertex,enums::usage indices)
	{
		_vertex_usage = vertex;
		_indices_usage = indices;
		self_type::describe();
	}
	void describe(enums::usage usage)
	{
		self_type::describe(usage, usage);
	}
	void describe()
	{
		base_type::describe(_vertex_usage, _indices_usage);
	}

	void resize(::std::size_t vertex_count)
	{
		base_type::layout().for_each_buffer([vertex_count](auto& buffer)
			{
				buffer.data().resize(vertex_count);
			});
		base_type::indices_buffer().data().resize(base_type::indices_size() + typename base_type::indices_buffer_type::indices_drawer_type::indices_count_of(vertex_count));

		self_type::describe();
	}

	decltype(auto) push_back_vertex_range(::std::ranges::sized_range auto&& vertex_range)
		requires ::std::indirectly_copyable<::std::ranges::iterator_t<decltype(vertex_range)>, ::std::ranges::iterator_t<typename base_type::layout_type>>
	{
		if (auto vertex_range_size = ::std::ranges::size(NGS_PP_PERFECT_FORWARD(vertex_range)); vertex_range_size > base_type::layout().size() - base_type::vertex_size())
		{
			self_type::resize(base_type::vertex_size() + vertex_range_size);
		}
		return base_type::push_back_vertex_range(NGS_PP_PERFECT_FORWARD(vertex_range));
	}

	decltype(auto) push_back_vertex_range(::std::initializer_list<typename base_type::vertex_type>&& vertex_range)
	{
		return self_type::push_back_vertex_range(vertex_range);
	}

	enums::usage _vertex_usage;
	enums::usage _indices_usage;
};

NGS_LIB_MODULE_END