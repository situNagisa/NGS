#pragma once

#include "../context.h"
#include "../reflect.h"
#include "../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct attribute
{
	size_t count;
	gl_enum_t type;
	bool normalized = false;
	size_t stride = 0;
	size_t offset = 0;
};

namespace _detail
{
	constexpr auto make_attribute(const reflect_data& data, bool normalized, size_t stride)
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
			auto field_data = mpl::mstruct::reflect<Buffer, reflecter>();

			return result_type{ (_detail::make_attribute(field_data[Index], normalized, mpl::mstruct::struct_size_v<Buffer>))... };
		}
	};

	template<class Buffer>
	constexpr auto make_attributes(bool normalized)
	{
		return make_attribute_from_variables<Buffer>::make(normalized);
	}
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

void vertex_draw_array(const contexts::vertex_array& array, enums::draw_mode draw_mode, ::std::size_t count, ::std::size_t offset = 0)
{

	NGS_EXTERNAL_OPENGL_CHECK(::glDrawArrays(static_cast<GLenum>(draw_mode), static_cast<GLint>(offset), static_cast<GLsizei>(count)));
}

void vertex_draw_elements(const contexts::vertex_array& array, enums::draw_mode draw_mode, ::std::size_t count, fundamental_t type, ::std::size_t offset = 0)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glDrawElements(static_cast<GLenum>(draw_mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), reinterpret_cast<const void*>(offset)));
}


NGS_LIB_MODULE_END