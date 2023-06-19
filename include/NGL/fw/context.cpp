#include "NGL/fw/context.h"

NGL_BEGIN

NGS_HPP_INLINE GLFW_Context GLFW_ContextManager::GetContext() { return { glfwGetCurrentContext() }; }
NGS_HPP_INLINE void GLFW_ContextManager::SetContext(GLFW_Context window) { glfwMakeContextCurrent(window); }

NGL_END

