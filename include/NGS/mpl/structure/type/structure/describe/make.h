#pragma once

#include "./describe.h"

NGS_LIB_MODULE_BEGIN

using structure_default_align_t = layout::no_align_t;

template<class...>
struct make_describe;

template<>
struct make_describe<> {
	using result_type = struct_describe<structure_default_align_t>;
};

template<class _First, class... _Rest>
struct make_describe< _First, _Rest...> {
private:
	constexpr static auto _GET() {
		constexpr size_t size = sizeof...(_Rest);
		using arg_type = _First;

		if constexpr (!size) {
			if constexpr (CStructureDescribe<arg_type>) {
				return declval<arg_type>();
			}
			else if constexpr (CVariable<arg_type>) {
				return declval<struct_describe<structure_default_align_t, arg_type>>();
			}
			else {
				return declval<struct_describe<structure_default_align_t, variable<arg_type>>>();
			}
		}
		else {
			if constexpr (layout::CAlign<arg_type>) {
				if constexpr ((CVariable<_Rest> && ...)) {
					return declval<struct_describe<arg_type, _Rest...>>();
				}
				else {
					return declval<struct_describe<
						arg_type,
						std::conditional_t<CVariable<arg_type>, _Rest, variable<_Rest>>...
						>>();
				}
			}
			else {
				return declval < struct_describe < structure_default_align_t,
					std::conditional_t<CVariable<arg_type>, arg_type, variable<arg_type>>,
					std::conditional_t<CVariable<arg_type>, _Rest, variable<_Rest>>...
					>>();
			}
		}
	}
public:
	using result_type = decltype(_GET());
};

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
template<class... _Types>
using make_describe_t = typename make_describe<_Types...>::result_type;

NGS_LIB_MODULE_END
