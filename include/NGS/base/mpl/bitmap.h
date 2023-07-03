#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/mpl/find.h"
#include "NGS/base/mpl/template_extraction.h"
#include "NGS/base/mpl/function.h"

NGS_BEGIN
NGS_MPL_BEGIN

template<class _Type, _Type _Value>
struct _bitmap_find_predicate {
	template<class _Input>
	struct meta_function {
		using type = typename _Input::first;
		constexpr static bool value = std::is_same_v<std::integral_constant<_Type, _Value>, typename _Input::second>;
	};
};

template <class _Type, _Type _Value, class... _Items>
struct _bitmap_find;

template <class _Type, _Type _Value, template<class...>class _Bitmap, class _First, class... _Items>
struct _bitmap_find<_Type, _Value, _Bitmap<_First, _Items...>> {
private:
	template<class _Input>
	using _meta_function = _bitmap_find_predicate<_Type, _Value>::template meta_function< _Input>;
	using _result = find_if<_meta_function, _First, _Items ... >;
public:
	using type = typename _result::type;
	constexpr static bool value = _result::value;
};

template<class _Key, uint32 _Value>
using bitmap_item = boost::mpl::pair<_Key, std::integral_constant<uint32, _Value>>;

template<class _Type, class... _Args>
struct bitmap {
	using type = boost::mpl::map<_Args...>;
private:
	template<class _Item>
	using _item_transformer = boost::mpl::pair<typename _Item::first, std::integral_constant<_Type, (_Type)_Item::second::value>>;
	using _transfomated = template_replace_transform_t<std::tuple<_Args...>, boost::mpl::map, _item_transformer>;
public:
	template<class _Key>
	constexpr static auto value = boost::mpl::at<type, _Key>::type::value;
	template<_Type _Value>
	using key = typename _bitmap_find<_Type, _Value, template_replace_transform_t<std::tuple<_Args...>, boost::mpl::map, _item_transformer>>::type;
};

NGS_END
NGS_END
