#pragma once

#include "./defined.h"
#include "./window.h"

NGS_EXTERNAL_GLFW_BEGIN

class NGS_DLL_API GLFW : public bases::singleton<GLFW> {
protected:
	NGS_MPL_ENVIRON(GLFW);

	using state_type = window;
private:
	friend class base_type;
	constexpr GLFW() = default;
public:
	~GLFW() { destroy(); }

	void initialize(int major, int minor);
	void init_opengl();
	void init_vulkan();

	void destroy();

	void select(state_type* window);
	bool state_same_as(const state_type* state)const { return _current == state; }
	auto&& get_current_state() const { return _current; }

	void poll_events();
	void terminate();
private:
	state_type* _current = nullptr;
};

NGS_EXTERNAL_GLFW_END