#pragma once

#include "./buffer.h"
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
	template<class T>
	concept gl_fundamental = cpt::fundamental<T> || (::std::is_bounded_array_v<T> && cpt::fundamental<::std::remove_all_extents_t<T>>);

	template<class T>
	struct is_fundamental : ::std::false_type {};

	template<template<class...> class Vector, mpl::mstruct::CVariable... Args>
	struct is_fundamental<Vector<Args...>> : ::std::bool_constant<(gl_fundamental<typename mpl::mstruct::variable_traits<Args>::original_type> && ...)> {};

	template<class T>
	concept fundamental_structure = /*mpl::mstruct::CFlattenedStructure<T> &&*/ is_fundamental<typename T::variable_types>::value;

	template<class T>
	constexpr auto make_attribute(const mpl::mstruct::variable_dynamic_data& data, bool normalized, size_t stride)
	{
		return attribute{ data.count, gl_convert<T>, normalized, stride, data.offset };
	}

	template<class Buffer, class = ::std::make_index_sequence<Buffer::variable_count>>
	struct make_attribute_from_variables;

	template<class Buffer, size_t... Index>
	struct make_attribute_from_variables<Buffer, ::std::index_sequence<Index...>>
	{
		static constexpr auto make(bool normalized)
		{
			using result_type = ::std::array<attribute, Buffer::variable_count>;
			auto variables = Buffer::get_variables();

			return result_type{ (_detail::make_attribute<
				::std::remove_all_extents_t<typename Buffer::template variable_at<Index>::original_type>
			>(variables[Index], normalized, Buffer::size))... };
		}
	};

	template<class Buffer>
	constexpr auto make_attributes(bool normalized)
	{
		return make_attribute_from_variables<Buffer>::make(normalized);
	}
}

//template<class...>
//constexpr auto create_vertex_descriptor(bool)
//{
//	return ::std::array<attribute, 0>{};
//}

template<_detail::fundamental_structure Buffer, _detail::fundamental_structure... Rest>
constexpr auto create_vertex_descriptor(bool normalized)
{
	if constexpr (!sizeof...(Rest))
	{
		using buffer_type = Buffer;

		return _detail::make_attributes<buffer_type>(normalized);
	}
	else
	{
		auto current_attributes = _detail::make_attributes<Buffer>(normalized);
		auto rest_attributes = create_vertex_descriptor<Rest...>(normalized);
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

NGS_LIB_MODULE_END