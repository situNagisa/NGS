#pragma once

#include "./binder.h"

NGS_LIB_MODULE_BEGIN

namespace detail {
	template<class...>
	struct binders;

	template<CBinder... _Binders>
	struct binders<_Binders...>
	{
		using structure_type = mpl::mstruct::flatten_as_struct_t<mpl::mstruct::structure<typename _Binders::structure_type...>>;

		constexpr static size_t binder_count = sizeof...(_Binders);
		constexpr static size_t attribute_count = (_Binders::attribute_count + ...);

		constexpr static auto binder_descriptions()
		{
			::std::array<vk::VertexInputBindingDescription, binder_count> descriptions{};
			::std::array<vk::VertexInputRate, binder_count> input_rates{ _Binders::input_rate... };

			for (size_t i = 0; i < descriptions.size(); ++i)
			{
				vk::VertexInputBindingDescription& d = descriptions[i];
				d.binding = static_cast<uint32_t>(i);
				d.stride = structure_type::size;
				d.inputRate = input_rates[i];
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

	template<class...> struct make_binders;

	/// @brief 生成绑定器
	///
	///	@tparam 
	template<class... _Types> using make_binders_t = typename make_binders<_Types...>::type;

	template<class>struct make_binder_from_sequence;
	template<template<class...>class _Template, class... _Types>
	struct make_binder_from_sequence<_Template<_Types...>>
	{
		using type = make_binder_t<_Types...>;
	};
	template<class... _Types> using make_binder_from_sequence_t = typename make_binder_from_sequence<_Types...>::type;

	template<class...> struct make_binders_sequence;
	template<class... _Types> using make_binders_sequence_t = typename make_binders_sequence<_Types...>::type;

	template<class... _Caches, class _First, class... _Types>
	struct make_binders_sequence<::boost::fusion::vector<_Caches...>, _First, _Types...>
	{
		using caches_type = ::boost::fusion::vector<_Caches...>;

		constexpr static auto get_cache_binder_type()
		{
			if constexpr (::boost::fusion::result_of::size<caches_type>::value)
			{
				return ngs::declval<::boost::fusion::vector<make_binder_from_sequence_t<caches_type>>>();
			}
			else
			{
				return ngs::declval<::boost::fusion::vector<>>();
			}
		}


		constexpr static auto get_type()
		{
			if constexpr (CBinder<_First>)
			{
				using cache_binder_type = type_traits::naked_t<decltype(get_cache_binder_type())>;
				using current_type = nboost::fusion::result_of::cat_t<cache_binder_type, ::boost::fusion::vector<_First>>;
				if constexpr (sizeof...(_Types))
				{
					using rest_type = make_binders_sequence_t<::boost::fusion::vector<>, _Types...>;
					return ngs::declval<nboost::fusion::result_of::cat_t<current_type, rest_type>>();
				}
				else
				{
					return ngs::declval<current_type>();
				}
			}
			else
			{
				using current_type = nboost::fusion::result_of::cat_t<caches_type, ::boost::fusion::vector<_First>>;
				if constexpr (sizeof...(_Types))
				{
					using rest_type = make_binders_sequence_t<current_type, _Types...>;
					return ngs::declval<rest_type>();
				}
				else
				{
					return ngs::declval<::boost::fusion::vector<make_binder_from_sequence_t<current_type>>>();
				}
			}
		}
		using type = type_traits::naked_t<decltype(get_type())>;
	};

	template<class>struct make_binders_from_sequence;
	template<template<class...>class _Template, CBinder... _Binders>
	struct make_binders_from_sequence<_Template<_Binders...>>
	{
		using type = binders<_Binders...>;
	};
	template<class... _Types> using make_binders_from_sequence_t = typename make_binders_from_sequence<_Types...>::type;

	template<class... _Types>
	struct make_binders
	{
		using type = make_binders_from_sequence_t<make_binders_sequence_t<::boost::fusion::vector<>, _Types...>>;
	};
}

template<class... _Types> using buffers = detail::make_binders_t<_Types...>;

NGS_LIB_MODULE_END