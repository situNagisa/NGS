#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace hints
{
	template<auto Hint, class Type>
	struct _hint
	{
		using type = Type;
		constexpr static auto hint = Hint;
	};

	constexpr static auto resizable = _hint<GLFW_RESIZABLE, bool>{};
	constexpr static auto visible = _hint<GLFW_VISIBLE, bool>{};
	constexpr static auto focused = _hint<GLFW_FOCUSED, bool>{};
	constexpr static auto auto_iconify = _hint<GLFW_AUTO_ICONIFY, bool>{};
	constexpr static auto decorated = _hint<GLFW_DECORATED, bool>{};
	constexpr static auto floating = _hint<GLFW_FLOATING, bool>{};
	constexpr static auto maximized = _hint<GLFW_MAXIMIZED, bool>{};
	constexpr static auto center_cursor = _hint<GLFW_CENTER_CURSOR, bool>{};
	constexpr static auto transparent_framebuffer = _hint<GLFW_TRANSPARENT_FRAMEBUFFER, bool>{};
	constexpr static auto hovered = _hint<GLFW_HOVERED, bool>{};
	constexpr static auto focus_on_show = _hint<GLFW_FOCUS_ON_SHOW, bool>{};
	constexpr static auto scale_to_monitor = _hint<GLFW_SCALE_TO_MONITOR, bool>{};
}

template<class T>
concept window_hint = requires
{
	{ type_traits::object_t<T>::hint };
	typename type_traits::object_t<T>::type;
};

template<window_hint Hint>
using hint_t = typename type_traits::object_t<Hint>::type;

template<window_hint Hint>
inline constexpr auto hint_v = type_traits::object_t<Hint>::hint;

NGS_LIB_MODULE_END