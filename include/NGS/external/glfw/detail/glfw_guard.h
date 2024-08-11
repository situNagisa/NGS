#pragma once

#include "./hint.h"
#include "./window.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class graphic_api
{
	opengl,
	vulkan,
};

struct basic_glfw_guard
{
	NGS_PP_INJECT_BEGIN(basic_glfw_guard);
public:
	basic_glfw_guard()
	{
		if (!glfwInit()) 
		{
			throw std::runtime_error("failed to initialize glfw");
		}
	}

	basic_glfw_guard(const self_type&) = delete;
	self_type& operator=(const self_type&) = delete;

	~basic_glfw_guard()
	{
		::glfwTerminate();
	}

	decltype(auto) create_window(auto&&... args)
	{
		return window(NGS_PP_PERFECT_FORWARD(args)...);
	}

	template<window_hint auto Hint>
	decltype(auto) set_hint(hint_t<decltype(Hint)> value) const noexcept
	{
		::glfwWindowHint(hint_v<decltype(Hint)>, value);
	}

	decltype(auto) swap_interval(int interval) const{ return ::glfwSwapInterval(interval); }
	decltype(auto) poll_events() const { return ::glfwPollEvents(); }
	decltype(auto) get_time() const { return ::glfwGetTime(); }
};

template<graphic_api Api>
struct glfw_guard;

template<>
struct glfw_guard<graphic_api::opengl> : basic_glfw_guard
{
	NGS_PP_INJECT(glfw_guard);
public:
	glfw_guard(int major, int minor)
	{
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

		if (major >= 3)
		{
			if (minor >= 2)
			{
				::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}
			if (minor >= 0)
			{
#if defined(NGS_SYSTEM_IS_MAC)
				::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
			}
		}
	}
};

template<>
struct glfw_guard<graphic_api::vulkan> : basic_glfw_guard
{
	NGS_PP_INJECT(glfw_guard);
public:
	glfw_guard()
	{
		::glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}
};

using opengl_guard = glfw_guard<graphic_api::opengl>;
using vulkan_guard = glfw_guard<graphic_api::vulkan>;

NGS_LIB_MODULE_END