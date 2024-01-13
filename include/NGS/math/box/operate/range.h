#pragma once

#include "../operator.h"
#include "../container.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	inline constexpr struct
	{
		constexpr decltype(auto) operator()(vectors::index_t index, auto box)const
		{
			return box->access(index);
		}
	}iterator_dereference{};

	template<class _Box>
	using iterator = vectors::vector_iterator<decltype(iterator_dereference(0, static_cast<_Box*>(nullptr))), iterator_dereference, _Box*>;
}

NGS_LIB_MODULE_END
NGS_MATH_BOX_OPERATOR_BEGIN

constexpr auto begin(box auto&& b) { return NGS_LIB_MODULE_NAME::_detail::iterator<type_traits::object_t<decltype(b)>>(0, &b); }
constexpr auto end(box auto&& b) { return NGS_LIB_MODULE_NAME::_detail::iterator<type_traits::object_t<decltype(b)>>(vectors::extent_v<decltype(b)>, &b); }
constexpr auto cbegin(const box auto& b) { return NGS_MATH_BOX_OPERATOR_NS::begin(b); }
constexpr auto cend(const box auto& b) { return NGS_MATH_BOX_OPERATOR_NS::end(b); }
constexpr auto rbegin(box auto&& b) { return ::std::make_reverse_iterator(NGS_MATH_BOX_OPERATOR_NS::end(b)); }
constexpr auto rend(box auto&& b) { return ::std::make_reverse_iterator(NGS_MATH_BOX_OPERATOR_NS::begin(b)); }
constexpr auto crbegin(const box auto& b) { return NGS_MATH_BOX_OPERATOR_NS::rbegin(b); }
constexpr auto crend(const box auto& b) { return NGS_MATH_BOX_OPERATOR_NS::rend(b); }

NGS_MATH_BOX_OPERATOR_END