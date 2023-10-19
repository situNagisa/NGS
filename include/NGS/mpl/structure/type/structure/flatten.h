#pragma once

#include "./structure.h"

NGS_STRUCTURE_TYPE_BEGIN

NGS_MPL_FUNCTION(flatten, class...);
template<class... _Types>
using flatten_t = typename flatten<_Types...>::result_type;

NGS_MPL_FUNCTION(flatten, class _First, class... _Rest) < boost::fusion::vector<_First, _Rest...> > {
private:
	constexpr static auto _GET_RESULT_TYPE() {
		using variable_type = std::conditional_t<CVariable<_First>, _First, variable<_First>>;
		using type = typename variable_type::storage_type;

		if constexpr (!(sizeof...(_Rest))) {
			if constexpr (CStructure<type>) {
				return declval<flatten_t<typename type::variable_types>>();
			}
			else {
				return declval<boost::fusion::vector<variable_type>>();
			}
		}
		else {
			if constexpr (CStructure<type>) {
				return declval<
					typename nboost::fusion::result_of::cat<
					flatten_t<typename type::variable_types>,
					flatten_t<boost::fusion::vector<_Rest...>>
					>::type
				>();
			}
			else {
				return declval<
					typename nboost::fusion::result_of::cat<
					boost::fusion::vector<variable_type>,
					flatten_t<boost::fusion::vector<_Rest...>>
					>::type
				>();
			}
		}
	}
public:
	NGS_MPL_TYPE result_type = decltype(_GET_RESULT_TYPE());
};

NGS_MPL_FUNCTION(flatten, CVariable... _Variables) < _Variables... > {
	using result_type = flatten_t<boost::fusion::vector<_Variables...>>;
};

NGS_MPL_FUNCTION(flatten, class... _Types) < _Types... > {
	using result_type = flatten_t<boost::fusion::vector<variable<_Types>...>>;
};


NGS_MPL_FUNCTION(flatten_as_struct, CStructure _Struct, class = flatten_t<_Struct>);
NGS_MPL_FUNCTION(flatten_as_struct, CStructure _Struct, template<class...>class _Sequence, CVariable... _Variables) < _Struct, _Sequence<_Variables...> > {
	NGS_MPL_TYPE result_type = structure<_Variables...>;
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

NGS_STRUCTURE_TYPE_END
