#pragma once

#include "../../enum.h"
#include "../../reflect.h"
#include "../../context.h"
#include "./descriptor.h"
#include "./group.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	struct attribute
	{
		size_t count;
		enums::buffer_vertex_fundamental type;
		bool normalized = false;
		size_t stride = 0;
		size_t offset = 0;
	};

	constexpr auto make_attribute(const reflects::buffer_vertex_data& data, bool normalized, size_t stride)
	{
		return attribute{ data.type.count, data.type.value, normalized, stride, data.offset };
	}

	template<class Buffer, class = ::std::make_index_sequence<mpl::mstruct::field_count_v<Buffer>>>
	struct make_attribute_from_variables;

	template<class Buffer, size_t... Index>
	struct make_attribute_from_variables<Buffer, ::std::index_sequence<Index...>>
	{
		static constexpr auto make(bool normalized)
		{
			using result_type = ::std::array<attribute, mpl::mstruct::field_count_v<Buffer>>;
			auto field_data = mpl::mstruct::reflect<Buffer, reflects::buffer_vertex_reflecter>();

			return result_type{ (_detail::make_attribute(field_data[Index], normalized, mpl::mstruct::struct_size_v<Buffer>))... };
		}
	};

	template<class Buffer>
	constexpr auto make_attributes(bool normalized)
	{
		return make_attribute_from_variables<Buffer>::make(normalized);
	}

	template<mpl::mstruct::structure Buffer, mpl::mstruct::structure... Rest>
	constexpr auto vertex_descriptor(bool normalized)
	{
		if constexpr (!sizeof...(Rest))
		{
			using buffer_type = Buffer;

			return _detail::make_attributes<buffer_type>(normalized);
		}
		else
		{
			auto current_attributes = _detail::make_attributes<Buffer>(normalized);
			auto rest_attributes = vertex_descriptor<Rest...>(normalized);
			constexpr auto attribute_count = current_attributes.size() + rest_attributes.size();
			using result_type = ::std::array<attribute, attribute_count>;
			result_type result{};
			for (size_t i = 0; i < current_attributes.size(); i++)
			{
				result[i] = current_attributes[i];
			}
			for (size_t i = 0; i < rest_attributes.size(); i++)
			{
				result[i + current_attributes.size()] = rest_attributes[i];
			}
			return result;
		}
	}

	template<buffer_descriptor Descriptor>
	auto install_buffer(cpt::naked_same_as<contexts::vertex_buffer> auto&& buffer, size_t index, ::std::span<const attribute> attributes)
	{
		using descriptor_type = Descriptor;
		contexts::bind(NGS_PP_PERFECT_FORWARD(buffer));
		::std::span<const attribute> buffer_attributes = ::std::ranges::subrange(attributes.begin() + static_cast<::std::ptrdiff_t>(index), attributes.begin() + static_cast<::std::ptrdiff_t>(index) + mpl::mstruct::field_count_v<descriptor_type>);
		for (const auto& [count, type, normalized, stride, offset] : buffer_attributes) {
			NGS_EXTERNAL_OPENGL_CHECK(::glEnableVertexAttribArray(static_cast<GLuint>(index)));
			NGS_EXTERNAL_OPENGL_CHECK(::glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(count), static_cast<GLenum>(type), normalized, static_cast<GLsizei>(stride), reinterpret_cast<void_ptr_cst>(offset)));
			index++;
		}
		return index;
	};

	template<buffer_descriptor... Descriptor>
	void pipeline_layout(const contexts::vertex_array& vertex_array, bool normalized, cpt::naked_same_as<contexts::vertex_buffer> auto&&... buffers)
		requires (sizeof...(Descriptor) == sizeof...(buffers))
	{
		NGS_EXTERNAL_OPENGL_EXPECT_BIND(vertex_array);
		auto attributes = _detail::vertex_descriptor<Descriptor...>(normalized);
		size_t index = 0;
		((index = _detail::install_buffer<Descriptor>(NGS_PP_PERFECT_FORWARD(buffers), index, attributes)), ...);
	}

	template<class>
	struct call_pipeline_layout;

	template<template<class...>class Template,class... Ts>
	struct call_pipeline_layout<Template<Ts...>>
	{
		static void call(const contexts::vertex_array& vertex_array, bool normalized, cpt::naked_same_as<contexts::vertex_buffer> auto&&... buffers)
		{
			_detail::pipeline_layout<type_traits::naked_t<Ts>...>(vertex_array, normalized, NGS_PP_PERFECT_FORWARD(buffers)...);
		}
	};

	void pipeline_layout(const contexts::vertex_array& vertex_array, bool normalized, cpt::derived_from_specialization<vertex_group> auto&& group)
	{
		::std::apply([&](auto&&... buffers)
			{
				call_pipeline_layout<typename decltype(group)::group_type>::call(vertex_array, normalized, NGS_PP_PERFECT_FORWARD(buffers)...);
			}, NGS_PP_PERFECT_FORWARD(group).get_group());
		
	}
}

struct vertex_array
{
	using context_type = contexts::vertex_array;

	explicit(false) vertex_array(cpt::derived_from_specialization<vertex_group> auto&& group, bool normalized = false)
	{
		contexts::bind(_context);
		_detail::pipeline_layout(_context, normalized, NGS_PP_PERFECT_FORWARD(group));
	}

	auto&& get_context() const noexcept
	{
		return _context;
	}

	context_type _context;
};

NGS_LIB_MODULE_END