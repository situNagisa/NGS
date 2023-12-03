#pragma once

#include "./binder.h"

NGS_LIB_MODULE_BEGIN

template<class...>
struct buffers;

template<CBinder... _Binders>
struct buffers<_Binders...>
{
	using sss = mpl::mstruct::structure<typename _Binders::structure_type...>;
	using structure_type = mpl::mstruct::flatten_as_struct_t<mpl::mstruct::structure<typename _Binders::structure_type...>>;

	constexpr static size_t binder_count = sizeof...(_Binders);
	constexpr static size_t attribute_count = (_Binders::attribute_count + ...);

	constexpr static auto binder_descriptions()
	{
		::std::array<vk::VertexInputBindingDescription, binder_count> descriptions{};

		for (size_t i = 0; i < descriptions.size(); ++i)
		{
			vk::VertexInputBindingDescription& d = descriptions[i];
			d.binding = static_cast<uint32_t>(i);
			d.stride = structure_type::size;
		}

		return descriptions;
	}
	constexpr static auto attribute_descriptions()
	{
		//get formats
		::std::array<vk::Format, attribute_count> formats{};
		{
			auto inserter = formats.begin();

			((inserter = ::std::ranges::copy(_Binders::formats, inserter).out), ...);
		}

		//get binding index
		::std::array<size_t, attribute_count> indexes{};
		{
			::std::array<size_t, binder_count> binder_sequence{ _Binders::attribute_count... };

			size_t inserter = 0;
			for (size_t i = 0; i < binder_sequence.size(); i++)
			{
				for (size_t j = 0; j < binder_sequence[i]; j++)
				{
					indexes[inserter] = i;
					inserter++;
				}
			}
		}

		::std::array<mpl::mstruct::variable_dynamic_data, attribute_count> variables = structure_type::get_variables();

		::std::array<vk::VertexInputAttributeDescription, attribute_count> descriptions{};

		for (size_t i = 0; i < descriptions.size(); ++i)
		{
			vk::VertexInputAttributeDescription& d = descriptions[i];
			d.format = formats[i];
			d.binding = static_cast<decltype(d.binding)>(indexes[i]);
			d.location = static_cast<decltype(d.location)>(i);
			d.offset = static_cast<decltype(d.offset)>(variables[i].offset);
		}

		return descriptions;
	}
};

NGS_LIB_MODULE_END