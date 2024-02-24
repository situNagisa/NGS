#pragma once

#include "../variable.h"
#include "./data.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<layout::align Align,variables::variable... Variables>
	struct descriptor
	{
		using fields_type = ::boost::fusion::vector<Variables...>;
		static constexpr ::std::size_t field_count = sizeof...(Variables);

		using align_type = Align;
		static constexpr ::std::size_t align = layout::align_as<align_type::value>(variables::variable_align_v<Variables>...);

		static constexpr ::std::size_t size = layout::size_of<align>(variables::variable_size_v<Variables>...);

		static constexpr auto reflect()
		{
			constexpr auto offsets = layout::offset<align>(variables::variable_size_v<Variables>...);

			return []<::std::size_t... Index>(::std::index_sequence<Index...>)
			{
				return ::std::array<variable_data,field_count>{
					variable_data{
						variables::variable_size_v<Variables>,
						offsets[Index],
						variables::variable_type_reflect_v<Variables>
					}...
				};
			}(::std::make_index_sequence<field_count>{});
		}
	};

	template<layout::align Align, class...>
	struct make_descriptor;

	template<layout::align Align>
	struct make_descriptor<Align> { using type = descriptor<Align>; };

	template<layout::align Align, class First, class... Rest>
	struct make_descriptor<Align, First, Rest...> {
	private:
		constexpr static auto _get() {
			using arg_type = First;

			if constexpr (!sizeof...(Rest)) {
				if constexpr (variables::variable<arg_type>) {
					return declval<descriptor<Align, arg_type>>();
				}
				else {
					return declval<descriptor<Align, variables::meta_variable<arg_type>>>();
				}
			}
			else {
				using result_type = descriptor<Align,
					std::conditional_t<variables::variable<arg_type>, arg_type, variables::meta_variable<arg_type>>,
					std::conditional_t<variables::variable<Rest>, Rest, variables::meta_variable<Rest>>...
				>;
				return declval<result_type>();
			}
		}
	public:
		using type = type_traits::naked_t<decltype(_get())>;
	};
}

/// @brief 生成一个`元结构体描述符`
///
///	@tparam CAlign,CAny 生成的`元结构体描述符`将采用`CAlign`作为对齐方式
///	@tparam CAny 生成的`元结构体描述符`将采用`structure_default_align_t`作为对齐方式，并将每个变量包装为`variable` 
///
///	@example
///	@code
///		make_describe_t<int, float, double> = struct_describe<structure_default_align_t, variable<int>, variable<float>, variable<double>>;
///		make_describe_t<ccpt::uint_<4>, int, float, double> = struct_describe<ccpt::uint_<4>, variable<int>, variable<float>, variable<double>>;
///		make_describe_t<variable<int>,variable<float>> = struct_describe<structure_default_align_t, variable<int>, variable<float>>;
///		make_describe_t<ccpt::uint_<4>, variable<int>, variable<float>> = struct_describe<ccpt::uint_<4>, variable<int>, variable<float>>;
///	@endcode
template<layout::align Align, class... Ts>
using meta_struct = typename _detail::make_descriptor<Align,Ts...>::type;


NGS_LIB_MODULE_END