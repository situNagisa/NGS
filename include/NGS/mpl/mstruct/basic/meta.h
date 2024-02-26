#pragma once

#include "../variable.h"
#include "./inherit.h"
#include "./defined.h"



NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<layout::align auto Align,variables::variable... Variables>
	struct descriptor
	{
		NGS_MPL_ENVIRON_BEGIN(descriptor);
	public:
		using fields_type = ::boost::fusion::vector<Variables...>;
		static constexpr ::std::size_t field_count = sizeof...(Variables);

		static constexpr layout::align_t align = layout::align_of(Align, variables::variable_align_v<Variables>...);

		static constexpr ::std::size_t size = layout::size_of<align.align()>(variables::variable_size_v<Variables>...);

		struct reflect_data {
			::std::size_t size;
			::std::size_t offset;
			variables::variable_type_t type;
		};

		static constexpr auto reflect()
		{
			constexpr auto offsets = layout::offset<align.align()>(variables::variable_size_v<Variables>...);

			return []<::std::size_t... Index>(::std::index_sequence<Index...>)
			{
				return ::std::array<reflect_data,field_count>{
					reflect_data{
						variables::variable_size_v<Variables>,
						offsets[Index],
						variables::variable_type_reflect_v<Variables>
					}...
				};
			}(::std::make_index_sequence<field_count>{});
		}

		template<class Self,class... Bases>
		struct _basic_inherit : _detail::inherit<Self,Bases...> {};
	};

	template<layout::align auto Align, class...>
	struct make_descriptor;

	template<layout::align auto Align>
	struct make_descriptor<Align> { using type = descriptor<Align>; };

	template<layout::align auto Align, class First, class... Rest>
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
template<layout::align auto Align, class... Ts>
struct meta_struct : _detail::make_descriptor<Align,Ts...>::type
{
	NGS_MPL_ENVIRON2(meta_struct, typename _detail::make_descriptor<Align, Ts...>::type);
public:
	template<class Self, class... Bases>
	using _basic_inherit = typename base_type::template _basic_inherit<Self, Bases...>;
	template<class... Bases>
	struct inherit : _basic_inherit<self_type,Bases...> {};
};


NGS_LIB_MODULE_END