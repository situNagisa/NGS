#pragma once

#include "./structure.h"

NGS_META_STRUCT_TYPE_BEGIN

NGS_mfunction(flatten, class...);
template<class... _Types>
using flatten_t = typename flatten<_Types...>::result_type;

NGS_mfunction(flatten, class _First, class... _Rest) < mpl::vector<_First, _Rest...> > {
private:
	constexpr static auto _GET_RESULT_TYPE() {
		using variable_type = std::conditional_t<CVariable<_First>, _First, variable<_First>>;
		using type = typename variable_type::storage_type;

		if constexpr (!(sizeof...(_Rest))) {
			if constexpr (CStructure<type>) {
				return declval<flatten_t<typename type::variable_types>>();
			}
			else {
				return declval<mpl::vector<variable_type>>();
			}
		}
		else {
			if constexpr (CStructure<type>) {
				return declval<mpl::push_front_range_t<flatten_t<mpl::vector<_Rest...>>, flatten_t<typename type::variable_types>>>();
			}
			else {
				return declval<mpl::push_front_t<flatten_t<mpl::vector<_Rest...>>, variable_type>>();
			}
		}
	}
public:
	NGS_mcst_t result_type = decltype(_GET_RESULT_TYPE());
};

NGS_mfunction(flatten, CVariable... _Variables) < _Variables... > {
	using result_type = flatten_t<mpl::vector<_Variables...>>;
};

NGS_mfunction(flatten, class... _Types) < _Types... > {
	using result_type = flatten_t<mpl::vector<variable<_Types>...>>;
};


NGS_mfunction(flatten_as_struct, CStructure _Struct, class = flatten_t<_Struct>);
NGS_mfunction(flatten_as_struct, CStructure _Struct, CVariable... _Variables) < _Struct, mpl::vector<_Variables...> > {
	NGS_mcst_t result_type = structure<_Variables...>;
};

/**
 * @brief 将结构体的元变量展开直至所有元变量都为基础变量
 *
 * @tparam _Struct 元结构体
 *
 * @return 展开后的元结构体
 */
template<CStructure _Struct>
using flatten_as_struct_t = typename flatten_as_struct<_Struct>::result_type;

NGS_META_STRUCT_TYPE_END
