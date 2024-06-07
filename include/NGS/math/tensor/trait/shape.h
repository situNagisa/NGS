#pragma once

#include "./max_dimension.h"
#include "./subtensor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	

	template<class T>
	struct shape_functor
	{
		NGS_CONFIG_STATIC_CALL_OPERATOR constexpr decltype(auto) operator()() NGS_CONFIG_STATIC_CALL_OPERATOR_CONST
		{
			using type = type_traits::naked_t<T>;

			//static member function
			if constexpr (requires{ type::shape(); })
			{
				return type::shape();
			}
			//adl
			else if constexpr (requires{ shape<type>(); })
			{
				return shape<type>();
			}
			else
			{
				::std::array<::std::size_t, max_dimension_of_v<type>> result{};
				[]<::std::size_t... Index>(auto&& result, ::std::index_sequence<Index...>)
				{
					((result[Index] = external::stl::ranges::algorithm::static_size<subtensor_t<type, Index>>()), ...);
				}(result, ::std::make_index_sequence<max_dimension_of_v<type>>{});
				return result;
			}
		}
	};
}

template<class T>
inline constexpr _detail::shape_functor<T> shape{};

NGS_LIB_MODULE_END
