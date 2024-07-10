#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
constexpr decltype(auto) combo(::std::string_view label, T& current_item, ::std::ranges::input_range auto&& items, ::std::ranges::input_range auto&& items_label)
	requires ::std::indirect_binary_predicate<::std::ranges::equal_to, ::std::ranges::iterator_t<decltype(items)>, T*>&& to_strings::stringable<::std::ranges::range_value_t<decltype(items_label)>>
{
	auto index = static_cast<int>(::std::ranges::distance(::std::ranges::begin(items), ::std::ranges::find(items, current_item)));

	auto labels = [](auto&& items_label) -> auto&& {
		if constexpr (cpt::naked_same_as<::std::ranges::range_value_t<decltype(items_label)>, const char*>)
		{
			if constexpr (::std::ranges::contiguous_range<decltype(items_label)>)
			{
				return NGS_PP_PERFECT_FORWARD(items_label);
			}
			else
			{
				static const auto c_str_labels = items_label | ::std::ranges::to<::std::vector<const char*>>();
				return c_str_labels;
			}
		}
		else
		{
			static const auto string_labels = items_label | ::std::views::transform([](const auto& item) { return to_strings::to_string(item); }) | ::std::ranges::to<::std::vector<::std::string>>();
			static const auto c_str_labels = string_labels | ::std::views::transform([](const auto& item) { return ::std::ranges::data(item); }) | ::std::ranges::to<::std::vector<const char*>>();
			return c_str_labels;
		}
		}(NGS_PP_PERFECT_FORWARD(items_label));

	auto is_change = ::ImGui::Combo(label.data(), &index, ::std::ranges::data(labels), ::std::ranges::size(labels));
	current_item = *::std::ranges::next(::std::ranges::begin(items), index);
	return is_change;
}

template<class T>
constexpr decltype(auto) combo(::std::string_view label, T& current_item, ::std::ranges::input_range auto&& items)
	requires ::std::indirect_binary_predicate<::std::ranges::equal_to, ::std::ranges::iterator_t<decltype(items)>, T*>
&& ::ngs::to_strings::stringable<::std::ranges::range_value_t<decltype(items)>>
{
	return NGS_LIB_MODULE_NAME::combo(label, current_item, NGS_PP_PERFECT_FORWARD(items), NGS_PP_PERFECT_FORWARD(items));
}

template<::std::ranges::input_range auto Items, class T>
	requires ::std::indirect_binary_predicate<::std::ranges::equal_to, ::std::ranges::iterator_t<decltype(Items | ::std::views::keys)>, T*>&& to_strings::stringable<::std::ranges::range_value_t<decltype(Items | ::std::views::values)>>
constexpr decltype(auto) combo(::std::string_view label, T& current_item)
{
	constexpr auto keys = Items | ::std::views::keys;
	constexpr auto values = Items | ::std::views::values;

	if constexpr (::ngs::cpt::naked_same_as<::std::ranges::range_value_t<decltype(values)>, const char*> && ::std::ranges::contiguous_range<decltype(values)>)
	{
		return NGS_LIB_MODULE_NAME::combo(label, current_item, keys, values);
	}
	else if constexpr (::std::convertible_to<::std::ranges::range_value_t<decltype(Items | ::std::views::values)>, const char*>)
	{
		constexpr auto c_str_labels = [values]
			{
				::std::array<const char*, ::std::ranges::size(values)> labels{};
				::std::ranges::copy(values, ::std::ranges::begin(labels));
				return labels;
			}();
		return NGS_LIB_MODULE_NAME::combo(label, current_item, keys, c_str_labels);
	}
	else
	{
		return NGS_LIB_MODULE_NAME::combo(label, current_item, keys, values);
	}
}

constexpr decltype(auto) combo(::std::string_view label, auto& current_item)
	requires ::std::is_enum_v<::ngs::type_traits::naked_t<decltype(current_item)>>
{
	using enum_type = ::ngs::type_traits::naked_t<decltype(current_item)>;

	return NGS_LIB_MODULE_NAME::combo(
		label,
		current_item,
		::std::views::iota(0) | ::std::views::take(::ngs::enums::contiguous_size<enum_type>()) | ::std::views::transform([](auto&& v) {return static_cast<enum_type>(v); }),
		enums::contiguous_names<enum_type>()
	);
}



NGS_LIB_MODULE_END