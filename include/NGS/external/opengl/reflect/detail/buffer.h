#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace buffers
{
	//indices

	namespace _detail
	{
		NGS_DECLARE_TV_DEFAULT(buffer_indices, enums::buffer_indices_fundamental, enums::buffer_indices_fundamental::none);
		NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, ::std::uint8_t, enums::buffer_indices_fundamental::unsigned_integral_8);
		NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, ::std::uint16_t, enums::buffer_indices_fundamental::unsigned_integral_16);
		NGS_DEFINE_TV(buffer_indices, enums::buffer_indices_fundamental, ::std::uint32_t, enums::buffer_indices_fundamental::unsigned_integral_32);
	}

	struct indices
	{
		using type = enums::buffer_indices_fundamental;

		template<class T>
		using reflect = ccpt::auto_constant<_detail::buffer_indices_convert<type_traits::naked_t<T>>>;
	};

	using indices_data = mpl::mstruct::basic::reflect_data<indices::type>;

	template<class T>
	concept indices_reflectable = indices::reflect<T>::value != enums::buffer_indices_fundamental::none;

	//uniform

	namespace _detail
	{
		NGS_DECLARE_TV_DEFAULT(buffer_uniform, enums::buffer_uniform_fundamental, enums::buffer_uniform_fundamental::none);
		NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, ::std::int32_t, enums::buffer_uniform_fundamental::integral);
		NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, ::std::uint32_t, enums::buffer_uniform_fundamental::unsigned_integral);
		NGS_DEFINE_TV(buffer_uniform, enums::buffer_uniform_fundamental, ::std::float_t, enums::buffer_uniform_fundamental::floating_point);
	}

	struct uniform
	{
		using type = enums::buffer_uniform_fundamental;

		template<class T>
		using reflect = ccpt::auto_constant<_detail::buffer_uniform_convert<type_traits::naked_t<T>>>;
	};

	using uniform_data = uniform::type;

	template<class T>
	concept uniform_reflectable = uniform::reflect<T>::value != enums::buffer_uniform_fundamental::none;

	// vertex

	namespace _detail
	{
		NGS_DECLARE_TV_DEFAULT(buffer_vertex, enums::buffer_vertex_fundamental, enums::buffer_vertex_fundamental::none);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::float_t, enums::buffer_vertex_fundamental::floating_point_32);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::double_t, enums::buffer_vertex_fundamental::floating_point_64);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::int8_t, enums::buffer_vertex_fundamental::integral_8);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::int16_t, enums::buffer_vertex_fundamental::integral_16);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::int32_t, enums::buffer_vertex_fundamental::integral_32);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::uint8_t, enums::buffer_vertex_fundamental::unsigned_integral_8);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::uint16_t, enums::buffer_vertex_fundamental::unsigned_integral_16);
		NGS_DEFINE_TV(buffer_vertex, enums::buffer_vertex_fundamental, ::std::uint32_t, enums::buffer_vertex_fundamental::unsigned_integral_32);

		//NGS_DEFINE_TV(buffer_vertex, fundamental_t, colors::primaries::RGBA24, GL_RGB);
		//NGS_DEFINE_TV(buffer_vertex, fundamental_t, colors::primaries::RGBA32, GL_RGBA);
	}

	struct vertex
	{
		struct type
		{
			enums::buffer_vertex_fundamental value;
			::std::size_t count;
		};

		template<class T>
		static constexpr auto _create()
		{
			using naked_type = type_traits::naked_t<T>;

			type result{ enums::buffer_vertex_fundamental::none,1 };

			if constexpr (::std::is_bounded_array_v<T>)
			{
				result.value = _detail::buffer_vertex_convert<::std::ranges::range_value_t<naked_type>>;
				result.count = ::std::extent_v<naked_type>;
			}
			else
			{
				result.value = _detail::buffer_vertex_convert<naked_type>;
			}

			//static_assert(result.value, "invalid type!");

			return result;
		}

		template<class T>
		using reflect = ccpt::auto_constant<_create<T>()>;
	};

	using vertex_data = mpl::mstruct::basic::reflect_data<vertex::type>;

	template<class T>
	concept vertex_reflectable = vertex::_create<T>().value != enums::buffer_vertex_fundamental::none;
}



NGS_LIB_MODULE_END